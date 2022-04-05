/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:58:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/21 13:40:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "Console.hpp"
#include "cmds/PingCommand.hpp"

PingCommand::PingCommand(void) {}
PingCommand::~PingCommand(void) {}

bool PingCommand::onCommand(User* sender, std::vector<std::string> args)
{
	(void) args;
	return sender->sendRawMessage("PONG :ft_irc");
}
