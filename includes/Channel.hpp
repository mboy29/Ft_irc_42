/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:50:00 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 12:05:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <cctype>
#include <string>
#include <User.hpp>

class Channel
{
	private:
		std::string							_name;
		std::string							_topic;
		std::vector<User*>					_users;

		User*								_creator;
		std::vector<User*>					_operators;

		std::multimap<char, std::string>	_modes;
		std::vector<User*>					_moderates;
		std::string							_password;
		std::size_t							_limit;

		std::vector<User *>					_banList;
		std::vector<User *>					_excepList;
		std::vector<User *>					_inviteList;


	public:
		Channel(std::string name, std::string topic);
		~Channel(void);

		bool				join(User* user);
		bool				leave(User* user);
		bool				kick(User* sender, User *target, std::string arg);

		int					contains(User* user);
		int					contains(std::string name);


		std::string			getName(void) const;
		std::string			getTopic(void) const;
		std::vector<User*>	getUsers(void) const;

		User*				getUser(std::string name);
		void				setTopic(std::string new_topic);


		void				rawBroadcast(std::string message, User* sender);
		void				broadcast(std::string code, std::string message, User* sender);

		void				setCreator(User *user);
		User				*getCreator(void) const;
		bool				isCreator(User *user) const;

		bool				isOperator(User *user) const;
		void				addOperator(User *user);
		void				deleteOperator(User *user);
		std::vector<User*>	getOperators(void) const;

		bool				isMode(char mode) const;
		bool 				isSetMode(char mode, std::string params) const;
		void				addMode(char mode, std::string params);
		void				deleteMode(char mode, std::string params);
		bool				setMode(std::string mode, std::string params);
		std::multimap<char, std::string>	getModes(void) const;

		bool 				isModerate(User *user) const;
		void				addModerate(User *user);
		void				deleteModerate(User *user);
		std::vector<User*>	getModerates(void) const;

		void 				setPassword(std::string pass);
		void				unsetPassword(void);
		std::string			getPassword(void) const;
		bool				isPassword(std::string pass) const;

		void				setLimit(std::string limit);
		void				unsetLimit(void);
		std::size_t			getLimit(void) const;
		bool				isFull(void) const;
		bool				checkLimit(std::string limit);

		std::string			getUsersList(void);

		bool 				isBanList(User *user) const;
		void				addBanList(User *user);
		void				deleteBanList(User *user);
		std::vector<User*>	getBanList(void) const;

		bool 				isExcepList(User *user) const;
		void				addExcepList(User *user);
		void				deleteExcepList(User *user);
		std::vector<User*>	getExcepList(void) const;


		bool 				isInviteList(User *user) const;
		void				addInviteList(User *user);
		void				deleteInviteList(User *user);
		std::vector<User*>	getInviteList(void) const;

};

#endif
