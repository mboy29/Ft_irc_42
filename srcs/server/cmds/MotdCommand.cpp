/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MotdCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:12:39 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 11:12:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cmds/MotdCommand.hpp"
#include "Console.hpp"
#include "Message.hpp"

MotdCommand::MotdCommand(Server *server) : _server(server) {};
MotdCommand::~MotdCommand(void) {}

bool	MotdCommand::onCommand(User *sender, std::vector<std::string> args)
{
	(void) args;

	sender->sendMessage(RPL_MOTDSTART, ":- ft_irc Message of the day - ");
	sender->sendMessage(RPL_MOTD, ":- " + _server->getMotd());
	sender->sendMessage(RPL_ENDOFMOTD, ":End of MOTD command");
	return (true);
}
