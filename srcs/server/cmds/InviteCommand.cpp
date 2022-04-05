/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:12:28 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 12:54:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cmds/InviteCommand.hpp"
#include "UserManager.hpp"
#include "Console.hpp"

InviteCommand::InviteCommand(Server *server) : _server(server) {}
InviteCommand::~InviteCommand(void) {}

static bool sendInvite(Server *server, User *sender, User *target, Channel *channel, std::vector<std::string> args)
{
	std::vector<std::string> privmsg;

	privmsg.push_back("PRIVMSG");
	privmsg.push_back(args[1]);
	privmsg.push_back(args[0] + " " + args[1] + " " + args[2]);
	server->getCommands().call("PRIVMSG", privmsg, sender);
	sender->sendMessage(RPL_INVITING, args[2] + " " + args[1]);
	channel->addInviteList(target);
	return (true);
}

bool	InviteCommand::onCommand(User* sender, std::vector<std::string> args)
{
	User	*target = NULL;
	Channel	*channel = NULL;

	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	if (args.size() != 3) {
		if (args.size() < 3)
			return (!sender->sendMessage(ERR_NEEDMOREPARAMS, args[0] + " :Not enough parameters"));
		return (false);
	}
	if (!(target = _server->getUsers().findbyNickname(args[1])))
		return (!sender->sendMessage(ERR_NOSUCHNICK, args[1] + " :No such nick/channel"));

	if (sender->getCurrentChannel() != args[2])
		return (!sender->sendMessage(ERR_NOTONCHANNEL, args[2] + " :You're not on that channel"));

	if (!(channel = _server->getChannels().get(args[2])))
		return (!sender->sendMessage(ERR_NOSUCHCHANNEL, args[2] + " :No such channel"));

	if (target->getCurrentChannel() == channel->getName())
		return (!sender->sendMessage(ERR_USERONCHANNEL, args[1] + " " + args[2] + " :is already on channel"));

	if (channel->isSetMode('i', "") && !channel->isOperator(sender))
		return (!sender->sendMessage(ERR_CHANOPRIVSNEEDED, args[2] + " :You're not channel operator"));
	return (sendInvite(_server, sender, target, channel, args));
}
