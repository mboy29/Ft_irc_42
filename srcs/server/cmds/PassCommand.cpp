/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:58:12 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 10:46:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/PassCommand.hpp"
#include "Server.hpp"
#include "Utils.hpp"

PassCommand::PassCommand(Server *server) : _server(server) {}
PassCommand::~PassCommand(void) {}

bool PassCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (sender->isConnected())
		return !sender->sendMessage(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)");

	if (args.size() != 2)
		return !sender->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");

	if (args[1] == _server->getPassword()) sender->setAccepted(true);
	else return !sender->sendMessage(ERR_PASSWDMISMATCH, ":Password incorrect");

	return sender->tryConnect();
}
