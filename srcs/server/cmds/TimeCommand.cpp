/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:12:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 12:53:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cmds/TimeCommand.hpp"
#include "Console.hpp"
#include "Message.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

TimeCommand::TimeCommand(Server *server) : _server(server) {};
TimeCommand::~TimeCommand(void) {}

bool	TimeCommand::onCommand(User *sender, std::vector<std::string> args)
{
	(void) args;

	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	time_t t = std::time(nullptr);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%A %d %B of %Y at %H:%M:%S");

	sender->sendMessage(RPL_TIME, "ft_irc :" + ss.str());
	return (true);
}
