/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:32:28 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/21 12:24:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include "Console.hpp"
#include "Utils.hpp"
#include "User.hpp"
#include "Message.hpp"

class Command
{
	public:
		virtual ~Command(void) {}
		virtual bool onCommand(User* sender, std::vector<std::string> args) = 0;
};

#endif
