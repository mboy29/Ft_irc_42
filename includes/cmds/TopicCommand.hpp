/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:58:14 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 10:58:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"

class TopicCommand : public Command
{
	protected:
		Server		*_server;

	public:
		TopicCommand(Server* sever);
		~TopicCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
