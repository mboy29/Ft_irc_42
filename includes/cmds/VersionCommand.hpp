/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VersionCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:58:21 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:58:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERSIONCOMMAND_HPP
#define VERSIONCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class VersionCommand : public Command
{
	protected:
		Server		*_server;

	public:
		VersionCommand(Server* sever);
		~VersionCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
