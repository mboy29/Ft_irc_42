/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MotdCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:57:51 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:57:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOTDCOMMAND_HPP
#define MOTDCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class MotdCommand : public Command
{
	protected:
		Server		*_server;

	public:
		MotdCommand(Server* sever);
		~MotdCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
