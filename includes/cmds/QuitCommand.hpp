/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/10 12:58:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <map>

class QuitCommand : public Command
{
	private:
		Server* _server;
	public:
		QuitCommand(Server* server);
		~QuitCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif

