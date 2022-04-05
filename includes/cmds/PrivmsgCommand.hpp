/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/21 14:43:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"

class PrivmsgCommand : public Command
{
	protected:
		Server* _server;
	public:
		PrivmsgCommand(Server* _server);
		~PrivmsgCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
