#include <unistd.h>
#include <cstdlib>
#include "cmds/ModeCommand.hpp"
#include "Console.hpp"
#include <iostream>
#include <sstream>

ModeCommand::ModeCommand(Server *server) : _server(server) {}
ModeCommand::~ModeCommand(void) {}


static bool	sendChannelMode(User *sender, Channel *channel)
{
	std::stringstream ss;
	std::multimap<char, std::string> modes = channel->getModes();

	ss << ":";
	for(std::multimap<char, std::string>::const_iterator it = modes.begin(); it != modes.end(); it++) {
		ss << "+" << it->first << " ";
		if (it->second != "")
			ss << it->second << " ";
	}
	return (sender->sendMessage(RPL_CHANNELMODEIS, channel->getName() + " " + ss.str()));
}

static bool	sendChannelMask(User *sender, Channel *channel, char mode)
{
	std::string	replay;
	std::vector<User*> list;
	std::pair<std::string, std::string>	end;

	switch (mode) {
		case 'b' : replay = RPL_BANLIST; list = channel->getBanList();
			end = std::pair<std::string, std::string>(RPL_ENDOFBANLIST, " :End of channel ban list"); break ;
		case 'e' :
			replay = RPL_EXCEPTLIST; list = channel->getExcepList();
			end = std::pair<std::string, std::string>(RPL_ENDOFEXCEPTLIST, " :End of channel exception list"); break ;
		case 'I' :
			replay = RPL_INVITELIST; list = channel->getInviteList();
			end = std::pair<std::string, std::string>(RPL_ENDOFINVITELIST, " :End of channel invite list"); break ;
	}
	for (std::size_t idx = 0; idx < list.size(); idx += 1)
		sender->sendMessage(replay, channel->getName() + " " + list[idx]->getNickname());
	return (sender->sendMessage(end.first, channel->getName() + end.second));
}

static bool	giveTakeChannelMode(User *sender, Channel *channel, std::pair<std::string, std::string> mode)
{
	User	*user = NULL;

	if (mode.second.empty() || !(user = channel->getUser(mode.second))) { // If param is empty or is an invalid user
		channel->deleteMode(mode.first[1], mode.second);
		if (mode.second.empty())
			return (!sender->sendMessage(ERR_NEEDMOREPARAMS, mode.first + " :Not enough parameters"));
		return(!sender->sendMessage(ERR_USERNOTINCHANNEL, channel->getName() + " :They aren't on that channel"));
	}

	else if (mode.first[1] == 'O') { // Give channel creator status
		if (channel->getName()[0] != '!' || mode.first[0] == '-') {
			channel->deleteMode(mode.first[1], mode.second);
			if (channel->getName()[0] != '!')
				return (!sender->sendMessage(ERR_NOCHANMODES, ":Restricted to safe channels"));
			return (!sender->sendMessage(ERR_NOCHANMODES, ":Channel creator can't be unset"));
		}
		channel->setCreator(user);
	}

	else if (mode.first[1] == 'o') // Give/take channel operator status
		(mode.first[0] == '+') ? channel->addOperator(user) : channel->deleteOperator(user);

	else if (mode.first[1] == 'v') // Give/take the voice privilege if channel mode -m
		(mode.first[0] == '+') ? channel->addModerate(user) : channel->deleteModerate(user);
	return (true);
}

static bool	toggleChannelMode(User *sender, Channel *channel, std::pair<std::string, std::string> mode)
{
	// Toggle the anonymous channel flag
	if (mode.first[1] == 'a') {
		if (channel->getName()[0] != '&' && channel->getName()[0] != '!') {
			channel->deleteMode(mode.first[1], mode.second);
			return (!sender->sendMessage(ERR_NOCHANMODES, ":Rectristed to safe and local channels"));
		}
		else if (channel->getName()[0] == '!' && !channel->isCreator(sender)) {
			channel->deleteMode(mode.first[1], mode.second);
			return (!sender->sendMessage(ERR_NOCHANMODES, ":Channel creator privileges required"));
		}
	}

	// Toggle the private/secret channel flag
	if ((mode.first[1] == 'p' && channel->isSetMode('s', "")) || (mode.first[1] == 's' && channel->isSetMode('p', ""))) {
		channel->deleteMode(mode.first[1], mode.second);
		return (!sender->sendMessage(ERR_NOCHANMODES, ":Secret/private channel mode conflict"));
	}

	// Toggle the server reop channel flag
	if (mode.first[1] == 'r' && (channel->getName()[0] != '!' || !channel->isCreator(sender))) {
		channel->deleteMode(mode.first[1], mode.second);
		if (channel->getName()[0] != '!')
			return (!sender->sendMessage(ERR_NOCHANMODES, ":Restricted to safe channels"));
		return (!sender->sendMessage(ERR_NOCHANMODES, ":Channel creator privileges required"));
	}
	return (true);
}

static bool setRemoveMaskChannelMode(User *sender, Channel *channel, Server* server, std::pair<std::string, std::string> mode)
{
	User	*user = NULL;
	std::vector<std::string> mask = Utils::str_split(mode.second, ",");

	if (mode.second.empty())
		return (!sender->sendMessage(ERR_NEEDMOREPARAMS, mode.first + " :Not enough parameters"));
	for (std::size_t idx = 0; idx < mask.size(); idx += 1) {
		if (!(user = channel->getUser(mask[idx])))
			return(!sender->sendMessage(ERR_USERNOTINCHANNEL, channel->getName() + " :They aren't on that channel"));
		if (mode.first[0] == '+' && channel->isSetMode(mode.first[1], mask[idx]))
			return (!sender->sendMessage(ERR_BADCHANMASK, channel->getName() + " :Channel key already set"));
		else if (!channel->setMode(mode.first, mask[idx])) {
			std::string	tmp = "";
			return (!sender->sendMessage(ERR_UNKNOWNMODE, tmp.append(1, mode.first[1]) + " :is unknown mode char to me for " + channel->getName()));
		}
		switch (mode.first[1]) {
			case 'b' : {
				if (mode.first[0] == '+')
				{
					channel->addBanList(user);
					std::vector<std::string> args;
					args.push_back("KICK");
					args.push_back(channel->getName());
					args.push_back(user->getNickname());
					args.push_back("Banned from channel for missconduct");
					server->getCommands().call("KICK", args, sender);
				}
				else channel->deleteBanList(user);
				break ;
			}
			case 'e' : (mode.first[0] == '+') ? channel->addExcepList(user) : channel->deleteExcepList(user); break ;
			case 'I' : (mode.first[0] == '+') ? channel->addInviteList(user) : channel->deleteInviteList(user); break ;
		}
	}
	return (sendChannelMask(sender, channel, mode.first[1]));
}

static bool	setRemoveChannelMode(User *sender, Channel *channel, std::pair<std::string, std::string> mode)
{
	if (mode.second == "" && mode.first != "-k" && mode.first != "-l") {
		channel->deleteMode(mode.first[1], mode.second);
		return (!sender->sendMessage(ERR_NEEDMOREPARAMS, mode.first + " :Not enough parameters"));
	}

	if (mode.first[1] == 'k') // Set/remove the channel key (password)
		(mode.first[0] == '+') ? channel->setPassword(mode.second) : channel->unsetPassword();

	if (mode.first[1] == 'l') { // Set/remove the user limit to channel
		if (!channel->checkLimit(mode.second)) {
			channel->deleteMode(mode.first[1], mode.second);
			return (!sender->sendMessage(ERR_NOCHANMODES, ":Require parameter of type digit (>= 0)"));
		}
		(mode.first[0] == '+') ? channel->setLimit(mode.second) : channel->unsetLimit();
	}
	return (true);
}

static bool	applyChannelMode(User *sender, Channel *channel, std::pair<std::string, std::string> mode)
{
	//  Modes that require a user parameter in order to give or take away a status
	if (mode.first[1] == 'O' || mode.first[1] == 'o' || mode.first[1] == 'v')
		return (giveTakeChannelMode(sender, channel, mode));

	//  Modes that require no parameter
	else if (mode.first[1] == 'a' || mode.first[1] == 'i' || mode.first[1] == 'm' || mode.first[1] == 'n' || mode.first[1] == 'q'
		|| mode.first[1] == 'p' || mode.first[1] == 's' || mode.first[1] == 'r' || mode.first[1] == 't')
		return (toggleChannelMode(sender, channel, mode));

	//  Modes that require a mask as a param
	else if (mode.first[1] == 'k' || mode.first[1] == 'l')
		return (setRemoveChannelMode(sender, channel, mode));
	return (true);
}

static bool	parseChannelMode(User *sender, Channel *channel, Server* server, std::vector<std::string> args)
{
	char	state;
	std::size_t	idxParam = 2;

	for (std::size_t idx = 0; idx < args[2].size(); idx += 1) {
		if (args[2][idx] == '+' || args[2][idx] == '-')
			state = args[2][idx];
		else {
			std::string param = "";
			std::stringstream ss;
			ss << state << args[2][idx];
			if (ss.str()[1] == 'o' || ss.str()[1] == 'O' || ss.str()[1] == 'v' || ss.str()[1] == 'l' || ss.str()[1] == 'k' || ss.str()[1] == 'b' || ss.str()[1] == 'e' || ss.str()[1] == 'I')
				param = ((idxParam + 1 < args.size()) ? args[++idxParam] : "");
			if ((ss.str()[1] == 'k' || ss.str()[1] == 'l') && ss.str()[0] == '+' && channel->isSetMode(ss.str()[1], ""))
				return (!sender->sendMessage(ERR_BADCHANMASK, channel->getName() + " :Channel key already set"));
			else if (ss.str()[0] == '+' && channel->isSetMode(ss.str()[1], param))
				return (!sender->sendMessage(ERR_BADCHANMASK, channel->getName() + " :Channel key already set"));
			if (ss.str()[1] == 'b' || ss.str()[1] == 'e' || ss.str()[1] == 'I') {
				if (!setRemoveMaskChannelMode(sender, channel, server, std::pair<std::string, std::string>(ss.str(), param)))
					return (false);
			}
			else {
				if (!channel->setMode(ss.str(), param)) {
					std::string	mode = "";
					return (!sender->sendMessage(ERR_UNKNOWNMODE, mode.append(1, ss.str()[1]) + " :is unknown mode char to me for " + channel->getName()));
				}
				if (!applyChannelMode(sender, channel, std::pair<std::string, std::string>(ss.str(), param)))
					return (false);
			}
		}
	}
	return (true);
}

static bool	ChannelMode(User *sender, Server *server, std::vector<std::string> args)
{
	Channel *channel = server->getChannels().get(args[1]);

	if (!channel)
		return !sender->sendMessage(ERR_NOSUCHCHANNEL, args[1] + " :No such channel");

	if (!channel->isOperator(sender))
		return (!sender->sendMessage(ERR_CHANOPRIVSNEEDED, args[1] + " :You're not channel operator"));

	if (channel->getName()[0] == '+')
		return (!sender->sendMessage(ERR_NOCHANMODES, args[1] + " :Channel doesn't support modes"));

	if (args.size() == 2)
		return (sendChannelMode(sender, channel));
	return (parseChannelMode(sender, channel, server, args));
}

static bool sendUserMode(User* sender)
{
	std::map<char, bool> modes = sender->getModes();
	std::stringstream ss;

	std::map<char, bool>::const_iterator first = modes.begin();
	std::map<char, bool>::const_iterator last = modes.end();

	ss << ":";
	for (std::map<char, bool>::const_iterator item = first; item != last; item++)
	{
		if ((*item).second)
			ss << '+' << (*item).first << " ";
	}
	return sender->sendMessage(RPL_UMODEIS, ss.str());
}

static bool parseUserMode(User* sender, std::vector<std::string> args)
{
	if (args[1] != sender->getNickname())
		return !sender->sendMessage(ERR_USERSDONTMATCH, ":Cannot change mode for other users");

	for (size_t i = 2; i < args.size(); i++)
	{
		if (args[i][0] != '+' && args[i][0] != '-')
			return !sender->sendMessage(ERR_UMODEUNKNOWNFLAG, ":Unknown MODE flag");
		for (size_t j = 1; j < args[i].size(); j++)
		{
			std::stringstream ss;
			ss << args[i][0] << args[i][j];
			if (!sender->useMode(ss.str()))
				return !sender->sendMessage(ERR_UMODEUNKNOWNFLAG, ":Unknown MODE flag");
		}
	}
	sendUserMode(sender);
	return true;
}

bool ModeCommand::onCommand(User* sender, std::vector<std::string> args)
{
	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	if (args.size() < 2)
		return !sender->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");

	if (args[1][0] == '&' || args[1][0] == '!' || args[1][0] == '+' || args[1][0] == '#')
		return ChannelMode(sender, _server, args);

	if (args[1] != sender->getNickname())
		return !sender->sendMessage(ERR_USERSDONTMATCH, ":Cannot change/seek mode for other users");

	if (args.size() == 2)
		return sendUserMode(sender);
	return parseUserMode(sender, args);
}
