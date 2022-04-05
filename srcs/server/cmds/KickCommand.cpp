#include "cmds/KickCommand.hpp"

KickCommand::KickCommand(Server *server) : _server(server) {}
KickCommand::~KickCommand(void) {}

bool	KickCommand::onCommand(User *sender, std::vector<std::string> args)
{
	User	*target = NULL;
	Channel	*channel = NULL;

	if (!sender->isConnected())
		return !sender->sendMessage(ERR_NOTREGISTERED, ":You have not registered");

	if (args.size() < 3)
		return (!sender->sendMessage(ERR_NEEDMOREPARAMS, args[0] + " :Not enough parameters"));

	if (!(channel = _server->getChannels().get(args[1])))
		return (!sender->sendMessage(ERR_NOSUCHCHANNEL, args[1] + " :No such channel"));

	if (sender->getCurrentChannel() != channel->getName())
		return (!sender->sendMessage(ERR_NOTONCHANNEL, channel->getName() + " :You're not on that channel"));

	if (!channel->isOperator(sender))
		return (!sender->sendMessage(ERR_CHANOPRIVSNEEDED, channel->getName() + " :You're not channel operator"));

	if (!(target = _server->getUsers().findbyNickname(args[2])))
		return (!sender->sendMessage(ERR_NOSUCHNICK, args[2] + " :No such nick/channel"));

	if (target->getCurrentChannel() != channel->getName())
		return (!sender->sendMessage(ERR_USERNOTINCHANNEL, target->getNickname() + " " + channel->getName() + " :They aren't on that channel"));

	if (args.size() == 3)
		return (channel->kick(sender, target, ""));
	return (channel->kick(sender, target, args[3]));
}
