/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:34:42 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/16 22:58:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "Command.hpp"

class UserCommand : public Command
{
	public:
		UserCommand(void);
		~UserCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif
