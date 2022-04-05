/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:58:08 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:58:09 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMECOMMAND_HPP
#define TIMECOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class TimeCommand : public Command
{
	protected:
		Server		*_server;

	public:
		TimeCommand(Server* sever);
		~TimeCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
