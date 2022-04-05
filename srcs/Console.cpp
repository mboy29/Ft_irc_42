/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:48:43 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 12:55:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Utils.hpp"

void Console::print(std::string type, std::string str, std::string color)
{
	std::cout << color << " " << type << " " << Console::RESET << " " << Utils::str_trim(str, "\n") << std::endl;
}

void Console::log(std::string str)
{
	Console::print("LOG", str, Console::BLUE);
}

void Console::error(std::string str)
{
	Console::print("ERROR", str, Console::RED);
}
