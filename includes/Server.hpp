/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:30:56 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/25 14:43:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/event.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "CommandManager.hpp"
#include "ChannelManager.hpp"
#include "UserManager.hpp"

#define CLIENT_MAX_COUNT	11

class Server
{
	private:
		int							_port;
		std::string					_password;
		std::string					_opPassword;
		std::string					_motd;
		std::string					_version;
		std::string					_versionComments;

		char						_opt;
		int							_server;
		struct sockaddr_in			_address;
		socklen_t					_addressSize;

		int							_kq;
		std::vector<struct kevent>	_changes;
		std::vector<struct kevent>	_events;

		CommandManager				_cmdsManager;
		ChannelManager				_channelManager;
		UserManager					_userManager;

	public:
		Server(int port, std::string password);
		~Server(void);

		void 			connect(void);

		std::string		getMotd(void) const;
		void			setMotd(std::string motd);
		std::string		getVersion(void) const;
		void			setVersion(std::string version);
		std::string		getVersionComments(void) const;
		void			setVersionComments(std::string comments);
		void			setOpPassword(std::string password);

		int				getPort(void) const;
		std::string		getPassword(void) const;
		std::string		getOpPassword(void) const;
		CommandManager&	getCommands(void);
		ChannelManager&	getChannels(void);
		UserManager&	getUsers(void);

};

#endif
