/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:57:50 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/04 15:41:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Utils.hpp"
#include "Console.hpp"
#include "User.hpp"

#include "cmds/PassCommand.hpp"
#include "cmds/UserCommand.hpp"
#include "cmds/NickCommand.hpp"
#include "cmds/JoinCommand.hpp"
#include "cmds/PrivmsgCommand.hpp"
#include "cmds/QuitCommand.hpp"
#include "cmds/TopicCommand.hpp"
#include "cmds/ModeCommand.hpp"
#include "cmds/PingCommand.hpp"
#include "cmds/PartCommand.hpp"
#include "cmds/MotdCommand.hpp"
#include "cmds/VersionCommand.hpp"
#include "cmds/TimeCommand.hpp"
#include "cmds/InviteCommand.hpp"
#include "cmds/OperCommand.hpp"
#include "cmds/ListCommand.hpp"
#include "cmds/KickCommand.hpp"
#include "cmds/NamesCommand.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password)
{
	// TODO: #4 Hash the password for more security

	setVersion("1.0");											// version du serveur
	setVersionComments("Premiere version public du server.");	// commentaire de la version
	setMotd("Le meilleur serveur irc de 42!");					// message du jour
	setOpPassword("operator");									// mot de passe des operators

	_cmdsManager.on("PASS", new PassCommand(this));
	_cmdsManager.on("USER", new UserCommand());
	_cmdsManager.on("NICK", new NickCommand(this));
	_cmdsManager.on("JOIN", new JoinCommand(this));
	_cmdsManager.on("PRIVMSG", new PrivmsgCommand(this));
	_cmdsManager.on("NOTICE", new PrivmsgCommand(this));
	_cmdsManager.on("QUIT", new QuitCommand(this));
	_cmdsManager.on("TOPIC", new TopicCommand(this));
	_cmdsManager.on("MODE", new ModeCommand(this));
	_cmdsManager.on("PING", new PingCommand());
	_cmdsManager.on("PART", new PartCommand(this));
	_cmdsManager.on("MOTD", new MotdCommand(this));
	_cmdsManager.on("VERSION", new VersionCommand(this));
	_cmdsManager.on("TIME", new TimeCommand(this));
	_cmdsManager.on("INVITE", new InviteCommand(this));
	_cmdsManager.on("OPER", new OperCommand(this));
	_cmdsManager.on("LIST", new ListCommand(this));
	_cmdsManager.on("KICK", new KickCommand(this));
	_cmdsManager.on("NAMES", new NamesCommand(this));

	_channelManager.add("#general", "Salon par default pour discuter de tout et de rien.");
	_channelManager.add("#test", "Salon pour effectuer des tests.");
}

Server::~Server(void) {}

void Server::connect(void)
{
	_server = socket(AF_INET, SOCK_STREAM, 0);
	_opt = 1;

	setsockopt(_server, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(int));

	std::memset((char*) &_address, 0, sizeof(_address));
	_address.sin_family			=	AF_INET;
	_address.sin_port			=	htons(_port);
	_address.sin_addr.s_addr	=	htons(INADDR_ANY);

	if (bind(_server, (struct sockaddr *) &_address, sizeof(_address)) < 0)
		Console::log("bind: error");

	fcntl(_server, F_SETFL, O_NONBLOCK);

	if (listen(_server, 42) < 0)
		Console::log("listen: error");

	_changes.resize(1);
	if ((_kq = kqueue()) == -1)
		Console::log("kqueue: failed init");

	EV_SET(_changes.begin().base(), _server, EVFILT_READ, EV_ADD, 0, 0, 0);

	Console::log("Server listening...");

	_addressSize = sizeof(_address);
	while (true)
	{
		_events.clear();
		_events.resize(1);
		int newEvents = kevent(
			_kq,
			_changes.begin().base(), _changes.size(),
			_events.begin().base(), _events.size(), NULL
		);
		if (newEvents < 0)
		{
			Console::error("kevent: error");
			break;
		}
		_changes.clear();

		for (int i = 0; i < newEvents; i++)
		{
			int event_fd = _events[i].ident;

			if (_events[i].flags & EV_ERROR)
				Console::error("kevent: EV_ERROR");
			if (_events[i].flags & EV_EOF)
			{
				User* user = _userManager.findBySocket(event_fd);
				if (user != NULL)
					_cmdsManager.call("QUIT", std::vector<std::string>(), user);
			}
			else if (event_fd == _server)
			{
				struct sockaddr_in client_addr;
				socklen_t client_len = sizeof(client_addr);
				int socket = accept(event_fd, (struct sockaddr *) &client_addr, &client_len);
				if (socket < 0)
					Console::error("accept: failed");

				_changes.resize(_changes.size() + 1);
				fcntl(socket, F_SETFL, O_NONBLOCK);
				EV_SET(_changes.end().base() - 1, socket, EVFILT_READ, EV_ADD, 0, 0, 0);

				_userManager.add(new User(socket, client_addr));

				_events.resize(_events.size() + 1);
				send(socket, "PING :Hello\r\n", 13, 0);
			}
			else if (_events[i].filter & EVFILT_READ)
			{
				char	buffer[1024];
				std::memset(buffer, 0, 1024);
				recv(event_fd, buffer, 1024, 0);

				if (std::string(buffer) == "\r\n")
					continue;

				if (std::strlen(buffer) > 511)
				{
					send(event_fd, "Limit message to 512 characteres\r\n", 34, 0);
					continue;
				}

				User* user = _userManager.findBySocket(event_fd);
				if (user == NULL)
					continue;

				if (std::string(buffer).find("\n") == std::string::npos)
				{
					user->_message += std::string(buffer);
					continue;
				}

				if (user->_message.empty())
					user->_message = std::string(buffer);

				std::vector<std::string> cmd_line = Utils::str_split(user->_message, "\n");
				for (size_t i = 0; i < cmd_line.size(); i++)
				{
					if (cmd_line[i].length() == 0)
						continue;

					Console::print("=> RECEIVED", cmd_line[i], Console::BLUE);

					std::vector<std::string> cmd_args = Utils::str_parse(cmd_line[i]);
					for (size_t j = 0; j < cmd_args.size(); j++)
						cmd_args[j] = Utils::str_trim(cmd_args[j], " \n\t\r\f\v");
					std::string cmd_name = Utils::str_trim(cmd_args[0], " \n\t\v\f\r");
					_cmdsManager.call(cmd_name, cmd_args, user);
				}
				user->_message.clear();
			}
		}
	}
	close(_server);

	Console::log("Server stopped...");
}

int Server::getPort(void) const
{ return _port; }

std::string Server::getPassword(void) const
{ return _password; }

std::string Server::getMotd(void) const
{ return _motd; }

void Server::setMotd(std::string motd)
{ _motd = motd; }

std::string Server::getVersion(void) const
{ return _version; }

void Server::setVersion(std::string version)
{ _version = version; }

std::string Server::getVersionComments(void) const
{ return _versionComments; }

void Server::setVersionComments(std::string comments)
{ _versionComments = comments; }

std::string Server::getOpPassword(void) const
{ return _opPassword; }

void Server::setOpPassword(std::string password)
{ _opPassword = password; }

CommandManager&	Server::getCommands(void) { return _cmdsManager; }
ChannelManager&	Server::getChannels(void) { return _channelManager; }
UserManager&	Server::getUsers(void) { return _userManager; }
