/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/10 13:11:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"

class PartCommand : public Command
{
	private:
		Server* _server;
	public:
		PartCommand(Server* server);
		~PartCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif

