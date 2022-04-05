/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:58:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/18 15:51:36 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "cmds/PrivmsgCommand.hpp"
#include <Utils.hpp>
#include "Console.hpp"
#include "Message.hpp"

PrivmsgCommand::PrivmsgCommand(Server* server) : _server(server) {}
PrivmsgCommand::~PrivmsgCommand(void) {}

bool PrivmsgCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	std::vector<std::string> list_of_to = Utils::str_split(args[1], ",");

	if (list_of_to.size() > 14) // ERR_TOOMANYTARGETS
		return !sender->sendMessage(ERR_TOOMANYTARGETS, ":407 recipients. Too many targets.");
	if (args.size() != 3) // ERR_NOTEXTTOSEND
		return !sender->sendMessage(ERR_NOTEXTTOSEND, ":No text to send");

	for (size_t i = 0; i < list_of_to.size(); i++)
	{
		User*		tmp_user = _server->getUsers().findbyNickname(list_of_to[i]);
		Channel*	tmp_chan = _server->getChannels().get(list_of_to[i]);

		if (tmp_user != NULL && tmp_chan == NULL)
			tmp_user->sendRawMessage(sender->to_string(false) + " PRIVMSG " + tmp_user->getNickname() + " :" + args[2]);
		else if (tmp_user == NULL && tmp_chan != NULL)
		{
			if (tmp_chan->isSetMode('m', "") && (!tmp_chan->isModerate(sender) && !tmp_chan->isOperator(sender)))
				continue;

			if (tmp_chan->isBanList(sender) && !tmp_chan->isExcepList(sender))
				continue;

			std::stringstream ss;
			ss << sender->to_string(tmp_chan->isSetMode('a', ""));
			ss << " PRIVMSG " + tmp_chan->getName() + " :" + args[2];
			tmp_chan->rawBroadcast(ss.str(), sender);
		}
	}
	return true;
}
