/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:34:42 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/10 15:55:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class ModeCommand : public Command
{
	protected:
		Server		*_server;

	public:
		ModeCommand(Server *server);
		~ModeCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
