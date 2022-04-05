/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:52:54 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/21 14:43:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESCOMMAND_HPP
#define NAMESCOMMAND_HPP

#include "Command.hpp"

class Server;

class NamesCommand : public Command
{
	protected:
		Server*	_server;
	public:
		NamesCommand(Server* server);
		~NamesCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
