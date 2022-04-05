/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:08:48 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/04 13:22:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cmds/JoinCommand.hpp"
#include "Console.hpp"

JoinCommand::JoinCommand(Server* server) : _server(server) {}
JoinCommand::~JoinCommand(void) {}

bool JoinCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (!sender->isConnected())
		return !sender->sendMessage(ERR_ALREADYREGISTRED, ":You have not registered");

	if (args.size() < 2)
		return !sender->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");


	Channel* channel = _server->getChannels().get(args[1]);
	if (channel == NULL)
	{
		channel = _server->getChannels().add(args[1], "");
		channel->addOperator(sender);
		channel->setCreator(sender);
	}
	// leave current channel
	Channel* tmp = _server->getChannels().get(sender->getCurrentChannel());
	if (tmp != NULL) tmp->leave(sender);

	if (channel->isFull())
		return (!sender->sendMessage(ERR_CHANNELISFULL, ":Limited to a certain amount of users."));

	if (channel->isSetMode('i', ""))
		return (!sender->sendMessage(ERR_INVITEONLYCHAN, ":Is invite-only."));

	if (channel->isBanList(sender) && !channel->isInviteList(sender) && !channel->isExcepList(sender))
		return (!sender->sendMessage(ERR_BANNEDFROMCHAN, ":You can't join because you're banned."));

	if (!channel->isSetMode('p', "")
		|| channel->isOperator(sender)
		|| channel->isInviteList(sender)
		|| channel->isCreator(sender)
		|| (args.size() == 3 && channel->isPassword(args[2])))
		channel->join(sender);
	else return !sender->sendMessage(ERR_NEEDREGGEDNICK, ":Cannot join channel (+p)");

	if (channel->getTopic() == "")
		sender->sendMessage(RPL_NOTOPIC, args[1] + " :No topic is set");
	else
		sender->sendMessage(RPL_TOPIC, args[1] + " :" + channel->getTopic());
	// TODO: #41 set @ before users' name when they are operators
	sender->sendMessage(RPL_NAMREPLY, "= " + args[1] + " :" + channel->getUsersList());
	sender->sendMessage(RPL_ENDOFNAMES, args[1] + " :End of NAMES list");
	if (channel->isInviteList(sender) && sender->getCurrentChannel() == channel->getName())
		channel->deleteInviteList(sender);
	return true;
}
