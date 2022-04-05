/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:58:12 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 10:46:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/NamesCommand.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "Message.hpp"

NamesCommand::NamesCommand(Server *server) : _server(server) {}
NamesCommand::~NamesCommand(void) {}

static bool sendChannelNames(User *sender, Channel *channel)
{
	if (channel == NULL)
		return false;
	if (channel->isSetMode('p', "") || channel->isSetMode('s', ""))
		return (true);
	std::stringstream ss;
	ss << "= " << channel->getName() << " :";
	ss << channel->getUsersList();
	sender->sendMessage(RPL_NAMREPLY, ss.str());
	sender->sendMessage(RPL_ENDOFNAMES, channel->getName() + " :End of NAMES list.");
	return true;
}

bool NamesCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	if (args.size() > 2)
		return !sender->sendMessage(ERR_NEEDMOREPARAMS, ":Too many parameters");

	if (args.size() == 2)
	{
		std::vector<std::string> channels = Utils::str_split(args[1], ",");
		if (channels.size() == 1)
			return sendChannelNames(sender, _server->getChannels().get(channels[0]));
		for (size_t i = 0; i < channels.size(); i++)
		{
			Channel *channel = _server->getChannels().get(channels[i]);
			if (channel != NULL) sendChannelNames(sender, channel);
		}
		return true;
	}

	std::map<std::string, Channel*> channels = _server->getChannels().getChannels();
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
		sendChannelNames(sender, it->second);

	return true;
}
