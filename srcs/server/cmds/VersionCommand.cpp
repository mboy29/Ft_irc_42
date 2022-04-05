/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VersionCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:13:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 12:52:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cmds/VersionCommand.hpp"
#include "Console.hpp"
#include "Message.hpp"

VersionCommand::VersionCommand(Server *server) : _server(server) {};
VersionCommand::~VersionCommand(void) {}

bool	VersionCommand::onCommand(User *sender, std::vector<std::string> args)
{
	(void) args;

	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	sender->sendMessage(RPL_VERSION, _server->getVersion() + " ft_irc :" + _server->getVersionComments());
	return (true);
}
