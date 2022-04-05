/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:58:18 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/04 15:27:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "Utils.hpp"
#include "cmds/NickCommand.hpp"

#define NICKNAME_MAX_SIZE 9

NickCommand::NickCommand(Server* server) : _server(server) {}
NickCommand::~NickCommand(void) {}

static bool checkNicknameValidity(std::string nickname)
{
	if (nickname.size() > NICKNAME_MAX_SIZE)
		return false;
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (!std::isalpha(nickname[i]) && !std::isdigit(nickname[i]))
			return false;
	}
	return true;
}

static bool checkNicknameAnonymous(std::map<std::string, Channel*> channels, std::string nickname)
{
	for (std::map<std::string, Channel*>::const_iterator it = channels.begin(); it != channels.end(); it++) {
		if (it->second->isSetMode('a', "") && nickname == "anonymous")
			return (true);
	}
	return (false);
}

static bool checkNicknameAvailability(Server* server, std::string nickname)
{
	std::map<int, User*> users = server->getUsers().getUsers();
	std::map<int, User*>::iterator begin = users.begin();
	for (; begin != users.end(); begin++)
		if (begin->second != NULL
			&& begin->second->isConnected()
			&& nickname == begin->second->getNickname())
			return false;
	return true;
}

bool NickCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (sender->isConnected() && sender->isMode('r'))
		return !sender->sendMessage(ERR_RESTRICTED, ":Your connection is restricted!");

	if (args.size() != 2 || args[1].length() == 0)
		return !sender->sendMessage(ERR_NONICKNAMEGIVEN, ":Not nickname given");

	if (!checkNicknameValidity(args[1])
		|| checkNicknameAnonymous(_server->getChannels().getChannels(), args[1]))
		return !sender->sendMessage(ERR_ERRONEUSNICKNAME, ":Erroneous nickname");

	if (!checkNicknameAvailability(_server, args[1]))
		return !sender->sendMessage(ERR_NICKNAMEINUSE, ":Nickname is already in use");

	if (!sender->getNickname().empty())
		sender->sendRawMessage(sender->to_string(false) + " NICK :" + args[1]);
	sender->setNickname(args[1]);

	return sender->tryConnect();
}
