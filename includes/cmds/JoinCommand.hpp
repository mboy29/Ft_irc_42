/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/21 14:41:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"

class JoinCommand : public Command
{
	protected:
		Server*	_server;
	public:
		JoinCommand(Server* sever);
		~JoinCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
