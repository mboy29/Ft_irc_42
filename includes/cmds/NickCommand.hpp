/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 13:27:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class NickCommand : public Command
{
	protected:
		Server		*_server;
		
	public:
		NickCommand(Server* server);
		~NickCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif

