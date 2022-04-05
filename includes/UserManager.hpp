/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:57:40 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/23 17:10:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <iostream>
#include <map>

#include "User.hpp"

class UserManager
{
	private:
		std::map<int, User*>	_users;

	public:
		UserManager(void) {}
		~UserManager(void) { _users.clear(); }

		void add(User* user)
		{
			_users.insert(std::pair<int, User*>(user->getSocket(), user));
		}

		User* findbyNickname(std::string nickname)
		{
			std::map<int, User*>::iterator begin = _users.begin();
			for (; begin != _users.end(); begin++)
				if (begin->second != NULL && nickname == begin->second->getNickname())
					return begin->second;
			return NULL;
		}

		bool contains(std::string nickname)
		{
			return this->findbyNickname(nickname) != nullptr;
		}

		bool contains(int socket) { return _users.count(socket) == 1; }

		User* findBySocket(int socket)
		{
			if (!this->contains(socket))
				return NULL;
			return _users[socket];
		}

		bool rename(std::string nickname, std::string newNickname)
		{
			if (this->contains(newNickname))
				return false;
			User* user = this->findbyNickname(nickname);
			if (user == NULL)
				return false;
			user->setNickname(newNickname);
			return true;
		}

		void remove(int socket)
		{
			_users.erase(socket);
		}

		int size(void) { return _users.size(); }

		std::map<int, User*> getUsers(void) { return _users; }
};

#endif
