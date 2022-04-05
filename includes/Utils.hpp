/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:36:34 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/15 14:58:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include "User.hpp"

namespace Utils
{
	std::vector<std::string> str_split(std::string str, std::string delimiters);

	std::vector<std::string> str_parse(std::string str);

	std::string str_ltrim(std::string str, const char* charset);
	std::string str_rtrim(std::string str, const char* charset);
	std::string str_trim(std::string str, const char* charset);

	std::string str_toupper(std::string str);
	std::string str_tolower(std::string str);
}


#endif
