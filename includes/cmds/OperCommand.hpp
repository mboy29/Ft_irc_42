/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:57:21 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:57:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERCOMMAND_HPP
#define OPERCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class OperCommand : public Command
{
	protected:
		Server		*_server;

	public:
		OperCommand(Server* sever);
		~OperCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
