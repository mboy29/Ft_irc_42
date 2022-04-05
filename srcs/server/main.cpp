/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:38 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/16 15:05:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

// Subject		:	https://cdn.intra.42.fr/pdf/pdf/39873/fr.subject.pdf
// RFC			:	https://datatracker.ietf.org/doc/html/rfc1459
// Multi-Socket	:	https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

static int print_usage(std::string exec)
{
	std::cerr << "usage: " << exec << " <port> <password>\n";
	return EXIT_FAILURE;
}

static bool print_error(std::string err)
{
	std::cerr << "error: " << err << std::endl;
	return false;
}

static bool check_number(std::string number)
{
	std::string::const_iterator it = number.begin();
    while (it != number.end() && std::isdigit(*it)) ++it;
    return (!number.empty() && it == number.end());
}

static bool check_args(int ac, char **av)
{
	if (ac != 3)
		return print_error("not enough arguments");
	if (!check_number(av[1]))
		return print_error("port must be numeric");
	return true;
}

int main(int ac, char **av)
{
	if (!check_args(ac, av))
		return print_usage(av[0]);

	Server server(
		std::atoi(av[1]),
		std::string(av[2])
	);
	server.connect();

	return EXIT_SUCCESS;
}

