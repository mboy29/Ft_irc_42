/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:17:02 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/11 14:35:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include <iostream>
#include <map>
#include "Channel.hpp"

class ChannelManager
{
	private:
		std::map<std::string, Channel*> _channels;

	public:
		ChannelManager(void) {}
		~ChannelManager(void) {}

		Channel*	add(std::string name, std::string topic)
		{
			Channel* chan = new Channel(name, topic);
			_channels[name] = chan;
			return chan;
		}

		bool	contains(std::string name)
		{
			return _channels.count(name) == 1;
		}

		bool	join(std::string name, User* user)
		{
			if (!this->contains(name))
				return false;
			return _channels[name]->join(user);
		}

		bool	leave(std::string name, User* user)
		{
			if (!this->contains(name))
				return false;
			return _channels[name]->leave(user);
		}

		Channel*	get(std::string name)
		{
			if (!this->contains(name))
				return NULL;
			return _channels[name];
		}

		void	remove(std::string name)
		{
			delete	_channels[name];
			_channels[name] = NULL;
		}

		std::map<std::string, Channel*> getChannels(void) const { return _channels; }
};

#endif
