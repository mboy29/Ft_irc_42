/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:57:42 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:57:45 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class InviteCommand : public Command
{
	protected:
		Server		*_server;

	public:
		InviteCommand(Server *sever);
		~InviteCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
