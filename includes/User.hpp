/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:31:04 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 10:48:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>
#include <sstream>
#include "Console.hpp"
#include "Message.hpp"

class User
{
	private:
		int						_socket;
		struct sockaddr_in		_address;

		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		std::string				_hostname;
		std::string				_servername;
		std::string				_currentChannel;
		std::string				_awayMessage;
		std::map<char, bool>	_modes;

		bool					_accepted;
		bool					_connected;

	public:
		std::string				_message;				

	public:
		User(int socket, struct sockaddr_in address)
			: _socket(socket), _address(address)
		{
			_nickname = "";
			_username = "";
			_realname = "";
			_hostname = "127.0.0.1";
			_servername = "";

			_accepted = false;
			_connected = false;
		}

		~User(void) {}

		bool		sendRawMessage(std::string message)
		{
			Console::print("<= SENT", message.c_str(), Console::GREEN);
			message += "\r\n";
			return send(this->getSocket(), message.c_str(), message.length(), 0) != -1;
		}

		bool		sendMessage(std::string code, std::string message)
		{
			std::stringstream ss;

			ss	<< ":ft_irc "
				<< code << " "
				<< this->getNickname() << " "
				<< message;

			return this->sendRawMessage(ss.str());
		}

		void		setCurrentChannel(std::string channel) { _currentChannel = channel; };
		void		setNickname(std::string nickname) { _nickname = nickname; }
		void		setUsername(std::string username) { _username = username; }
		void		setRealname(std::string realname) { _realname = realname; }
		void		setHostname(std::string hostname) { _hostname = hostname; }
		void		setServername(std::string servername) { _servername = servername; }

		void		setAwayMessage(std::string message) { _awayMessage = message; }

		void		setMode(char mode, bool state) { _modes[mode] = state; }
		void		addMode(char mode) { setMode(mode, true); }
		void		removeMode(char mode) { setMode(mode, false); }
		bool		useMode(std::string mode)
		{
			if (mode.size() != 2)
				return false;
			if (mode[0] != '+' && mode[0] != '-')
				return false;
			if (mode[1] != 'a' && mode[1] != 'i' && mode[1] != 'w' && mode[1] != 'r'
				&& mode[1] != 'o' && mode[1] != 'O' && mode[1] != 's')
				return false;
			if (mode[0] == '+' && mode[1] != 'o' && mode[1] != 'O' && mode[1] != 'a')
				addMode(mode[1]);
			if (mode[0] == '-' && mode[1] != 'a')
				removeMode(mode[1]);
			return true;
		}
		bool		hasMode(char mode) { return _modes.count(mode) == 1; }
		bool		isMode(char mode)
		{
			if (!hasMode(mode))
				return false;
			return _modes[mode];
		}

		void		setAccepted(bool accepted) { _accepted = accepted; }
		bool		isAccepted(void) { return _accepted; }

		void		setConnected(bool connected) { _connected = connected; }
		bool		isConnected(void) { return _connected; }
		bool		tryConnect(void) {
			if (isConnected() || !isAccepted() || getUsername().empty() || getNickname().empty())
				return false;

			setConnected(true);
			sendMessage(RPL_WELCOME, ":Welcome to the Internet Relay Network " + to_string(false));
			Console::print("+ USER", to_string(false) + " has join", Console::PURPLE);
			return true;
		}

		int			getSocket(void) const { return _socket; }
		std::string	getCurrentChannel(void) const { return _currentChannel; }
		std::string	getNickname(void) const { return _nickname; }
		std::string	getUsername(void) const { return _username; }
		std::string	getRealname(void) const { return _realname; }
		std::string	getHostname(void) const { return _hostname; }
		std::string	getServername(void) const { return _servername; }
		std::string getAwayMessage(void) const { return _awayMessage; }
		std::string	getAddress(void) const { return inet_ntoa(_address.sin_addr); }
		int			getPort(void) const { return ntohs(_address.sin_port); }
		std::map<char, bool> getModes(void) const { return _modes; }

		std::string	to_string(bool isAnon) const
		{
			if (isAnon)
				return ":anonymous!anonymous@anonymous";
			return (":" + _nickname + "!" + _username + "@" + this->getAddress());
		}
};

#endif
