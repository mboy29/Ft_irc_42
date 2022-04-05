/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:57:50 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 16:00:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include "Utils.hpp"
#include "Console.hpp"

Bot::Bot(std::string host, int port, std::string password)
	: _host(host), _port(port), _password(password)
{
	_server = socket(AF_INET, SOCK_STREAM, 0);
	_opt = 1;

	setsockopt(_server, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(int));

	std::memset((char*) &_address, 0, sizeof(_address));
	_address.sin_family			=	AF_INET;
	_address.sin_port			=	htons(_port);
	_address.sin_addr.s_addr	=	inet_addr(_host.c_str());
}

void Bot::connect(std::string channel)
{
	::connect(_server, (struct sockaddr *) &_address, sizeof(_address));

	std::string msg_pass = "PASS :" + _password + "\r\n";
	send(_server, msg_pass.c_str(), msg_pass.size(), 0);

	std::string msg_nick = "NICK ircbot\r\n";
	send(_server, msg_nick.c_str(), msg_nick.size(), 0);

	std::string msg_user = "USER ircbot ircbot * :ircbot\r\n";
	send(_server, msg_user.c_str(), msg_user.size(), 0);

	std::string msg_join = "JOIN #" + channel + "\r\n";
	send(_server, msg_join.c_str(), msg_join.size(), 0);

	Console::log("Bot listening...");

	_addressSize = sizeof(_address);
	_running = true;
	while (_running)
	{
		char buffer[1024];
		std::memset(buffer, 0, 1024);
		recv(_server, buffer, 1024, 0);

		if (std::string(buffer).empty() || std::string(buffer) == "\r\n")
			continue;

		if (std::strlen(buffer) > 511)
		{
			send(_server, "Limit message to 512 characteres\r\n", 34, 0);
			continue;
		}

		std::vector<std::string> cmd_line = Utils::str_split(buffer, "\n");
		for (size_t i = 0; i < cmd_line.size(); i++)
		{
			if (cmd_line[i].length() == 0)
				continue;

			std::vector<std::string> tmp_args = Utils::str_parse(cmd_line[i]);
			for (size_t j = 0; j < tmp_args.size(); j++)
				tmp_args[j] = Utils::str_trim(tmp_args[j], " \n\t\r\f\v");

			Console::print("=> RECEIVED", cmd_line[i], Console::BLUE);

			if (std::strstr(cmd_line[i].c_str(), "PING") != NULL)
			{
				std::string pong = "PONG :" + tmp_args[1] + "\r\n";
				send(_server, pong.c_str(), pong.size(), 0);
				Console::print("<= SENT", pong, Console::GREEN);
			}
			else if (std::strstr(cmd_line[i].c_str(), "PRIVMSG") != NULL)
			{
				std::string cmd_location = tmp_args[2];
				std::vector<std::string> cmd_args = Utils::str_parse(tmp_args[3]);
				for (size_t j = 0; j < cmd_args.size(); j++)
					cmd_args[j] = Utils::str_trim(cmd_args[j], " \n\t\r\f\v");
				std::string cmd_name = Utils::str_trim(cmd_args[0], " \n\t\v\f\r");

				this->onCommand(cmd_location, cmd_name, cmd_args);
			}
		}
	}
	close(_server);
}

bool Bot::onCommand(std::string location, std::string name, std::vector<std::string> args)
{
	(void) args;

	if (name == "!ping")
		return this->reply(location, "pong!");

	if (name == "!help")
		return this->reply(location, "I'm sorry Dave, I'm afraid I can't do that.");

	if (name == "!ciao") this->stop();

	return false;
}

void Bot::stop(void)
{
	_running = false;
}

bool Bot::reply(std::string location, std::string msg)
{
	std::string msg_reply = "PRIVMSG " + location + " :" + msg + "\r\n";
	send(_server, msg_reply.c_str(), msg_reply.size(), 0);
	Console::print("<= SENT", msg_reply, Console::GREEN);
	return true;
}

std::string Bot::getHost(void) const
{ return _host; }

int Bot::getPort(void) const
{ return _port; }

std::string Bot::getPassword(void) const
{ return _password; }
