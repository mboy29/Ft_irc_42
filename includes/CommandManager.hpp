/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:49:52 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/15 15:03:19 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "Utils.hpp"

#include "cmds/Command.hpp"

class CommandManager
{
	private:
		std::map<std::string, Command*>	_cmds;

	public:
		CommandManager(void) { }
		~CommandManager(void) { _cmds.clear(); }

		/**
		 * @brief Check if the CommandManager listen to a specific Command.
		 *
		 * @param cmd_name	The Command's name
		 * @return			true if the CommandManager is listening to the Command.
		 */
		bool has(std::string cmd_name)
		{
			return _cmds.count(Utils::str_toupper(cmd_name)) == 1;
		}

		/**
		 * @brief Register a Command to the CommandManager so it can be called later on.
		 *
		 * @param cmd_name	The command's name.
		 * @param cmd		The command's pointer.
		 */
		void on(std::string cmd_name, Command* cmd)
		{
			 _cmds[Utils::str_toupper(cmd_name)] = cmd;
		}

		/**
		 * @brief Search a Command pointer by it's name and call it's onCommand member method.
		 *
		 * @param cmd		The command's name.
		 * @param args		Every arguments of the command line.
		 * @param sender	The user that sent the command line.
		 * @return			true if the command succeeded, false otherwise.
		 */
		bool call(std::string cmd_name, std::vector<std::string> args, User* sender)
		{
			if (!this->has(cmd_name))
				return false;
			return _cmds[Utils::str_toupper(cmd_name)]->onCommand(sender, args);
		}
};

#endif
