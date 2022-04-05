/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:52:54 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/21 14:43:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "Command.hpp"

class Server;

class PassCommand : public Command
{
	protected:
		Server*	_server;
	public:
		PassCommand(Server* server);
		~PassCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
