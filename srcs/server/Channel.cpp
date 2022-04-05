#include "Channel.hpp"

//  Constructor & Destructor :
//  ----------------------------------------------------

Channel::Channel(std::string name, std::string topic) : _name(name), _topic(topic), _password(""), _limit(-1) {}
Channel::~Channel(void) {}

//  Join & Leave Channel :
//  ----------------------------------------------------

bool	Channel::join(User* user)
{
	user->setCurrentChannel(_name);
	_users.push_back(user);
	rawBroadcast(user->to_string(isSetMode('a', "")) + " JOIN " + getName(), user);
	user->sendRawMessage(user->to_string(isSetMode('a', "")) + " JOIN " + getName());
	return (true);
}

bool	Channel::leave(User* user)
{
	int index;
	if ((index = this->contains(user)) < 0)
		return false;
	user->sendRawMessage(user->to_string(isSetMode('a', "")) + " PART :" + getName());
	rawBroadcast(user->to_string(isSetMode('a', "")) + " PART :" + getName(), user);
	user->setCurrentChannel("");
	_users.erase(_users.begin() + index);
	return true;
}

bool	Channel::kick(User* sender, User *target, std::string arg)
{
	int index;
	if ((index = this->contains(target)) < 0)
		return false;
	if (arg.empty()) {
		target->sendRawMessage(sender->to_string(isSetMode('a', "")) + " KICK " + getName() + " " + target->getNickname());
		rawBroadcast(sender->to_string(isSetMode('a', "")) + " KICK " + getName() + " " + target->getNickname(), target);
	}
	else {
		target->sendRawMessage(sender->to_string(isSetMode('a', "")) + " KICK " + getName() + " " + target->getNickname() + " :" + arg);
		rawBroadcast(sender->to_string(isSetMode('a', "")) + " KICK " + getName() + " " + target->getNickname() + " :" + arg, target);
	}
	target->setCurrentChannel("");
	_users.erase(_users.begin() + index);
	return true;
}

//  Channel contains user :
//  ----------------------------------------------------

int		Channel::contains(User* user)
{
	size_t index = 0;
	while (index < _users.size())
	{
		if (user->getUsername() == _users[index]->getUsername())
			return index;
		index++;
	}
	return -1;
}

int		Channel::contains(std::string name)
{
	for (std::size_t idx = 0; idx < _users.size(); idx += 1) {
		if (_users[idx]->getUsername() == name)
			return (idx);
	}
	return (-1);
}

//  Get & Set member types :
//  ----------------------------------------------------

std::string			Channel::getName(void) const { return _name; }
std::vector<User*>	Channel::getUsers(void) const { return _users; }

User*				Channel::getUser(std::string name)
{
	for (std::size_t idx = 0; idx < _users.size(); idx += 1) {
		if (_users[idx]->getUsername() == name)
			return (_users[idx]);
	}
	return (NULL);
}

void				Channel::setTopic(std::string new_topic) { this->_topic = new_topic; }
std::string			Channel::getTopic(void) const { return _topic; }


//  Broadcast :
//  ----------------------------------------------------

void	Channel::rawBroadcast(std::string message, User* sender)
{
	size_t i = 0;
	while (i < _users.size())
	{
		if (_users[i]->getUsername() != sender->getUsername()
			&& _users[i]->getCurrentChannel() == _name)
			_users[i]->sendRawMessage(message);
		i++;
	}
}

void	Channel::broadcast(std::string code, std::string message, User* sender)
{
	size_t i = 0;
	while (i < _users.size())
	{
		if (_users[i]->getUsername() != sender->getUsername()
			&& _users[i]->getCurrentChannel() == _name)
			_users[i]->sendMessage(code, message);
		i++;
	}
}

//  Creator :
//  ----------------------------------------------------

void				Channel::setCreator(User *user) { _creator = user ;}
User				*Channel::getCreator(void) const { return (_creator); }

bool				Channel::isCreator(User *user) const {
	if (user == _creator)
		return (true);
	return (false);
}

//  Operators :
//  ----------------------------------------------------

std::vector<User*>	Channel::getOperators(void) const { return (_operators); }

bool	Channel::isOperator(User *user) const
{
	for (std::size_t idx = 0; idx < _operators.size(); idx += 1) {
		if (_operators[idx] == user)
			return (true);
	}
	return (false);
}

void	Channel::addOperator(User *user)
{
	if (!isOperator(user))
		_operators.push_back(user);
}

void	Channel::deleteOperator(User *user)
{
	if (!isOperator(user))
		return ;
	for (std::vector<User*>::const_iterator it = _operators.begin(); it != _operators.end(); it++) {
		if (*it == user)
			return ((void)_operators.erase(it));
	}
}

//  Mode :
//  ----------------------------------------------------

std::multimap<char, std::string>	Channel::getModes(void) const { return (_modes); }

bool	Channel::isMode(char mode) const
{
	std::string		validModes = "OovaimnqpsrtklbeI";

	for (std::size_t idx = 0; idx < validModes.size(); idx += 1) {
		if (mode == validModes[idx])
			return (true);
	}
	return (false);
}

bool 	Channel::isSetMode(char mode, std::string params) const
{
	for (std::multimap<char, std::string>::const_iterator it = _modes.begin(); it != _modes.end(); it++) {
		if (it->first == mode && it->second == params)
			return (true);
	}
	return (false);
}

void	Channel::addMode(char mode, std::string params)
{
	for (std::multimap<char, std::string >::const_iterator it = _modes.begin(); it != _modes.end(); it++) {
		if (it->first == mode && it->second == params) {
			_modes.erase(it);
			break ;
		}
	}
	_modes.insert(std::pair<char, std::string>(mode, params));
}

void	Channel::deleteMode(char mode, std::string params)
{
	for (std::multimap<char, std::string >::const_iterator it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->first == mode && it->second == params)
			return ((void)_modes.erase(it));
	}
}

bool	Channel::setMode(std::string mode, std::string params)
{
	if ((mode[0] != '+' && mode[0] != '-') || !isMode(mode[1]))
		return (false);
	if (mode[0] == '+')
		addMode(mode[1], params);
	else if (mode[0] == '-')
		deleteMode(mode[1], params);
	return (true);
}


//  Moderate :
//  ----------------------------------------------------

std::vector<User*>	Channel::getModerates(void) const { return (_operators); }

bool	Channel::isModerate(User *user) const
{
	for (std::size_t idx = 0; idx < _moderates.size(); idx += 1) {
		if (_moderates[idx] == user)
			return (true);
	}
	return (false);
}

void	Channel::addModerate(User *user)
{
	if (!isModerate(user))
		_moderates.push_back(user);
}

void	Channel::deleteModerate(User *user)
{
	if (!isModerate(user))
		return ;
	for (std::vector<User*>::const_iterator it = _moderates.begin(); it != _moderates.end(); it++) {
		if (*it == user)
			return ((void)_moderates.erase(it));
	}
}

//  Password :
//  ----------------------------------------------------

void 				Channel::setPassword(std::string pass) { _password = pass ;}
void				Channel::unsetPassword(void) { _password = ""; }
std::string			Channel::getPassword(void) const { return (_password); }

bool				Channel::isPassword(std::string pass) const {
	if (!_password.empty() && pass == _password)
		return (true);
	return (false);
}

//  Limit :
//  ----------------------------------------------------

void				Channel::setLimit(std::string limit) { _limit = stoi(limit); }
void				Channel::unsetLimit(void) { _limit = -1; }
std::size_t			Channel::getLimit(void) const { return (_limit); }

bool				Channel::isFull(void) const {
	if (_users.size() >= _limit)
		return (true);
	return (false);
}

bool		Channel::checkLimit(std::string limit) {
	for (std::size_t idx = 0; idx < limit.size(); idx += 1) {
		if (isdigit(limit.at(idx)) == false)
			return (false);
	}
	return (true);
}

//  Banned Mask :
//  ----------------------------------------------------

std::vector<User*>	Channel::getBanList(void) const { return (_banList); }

bool	Channel::isBanList(User *user) const
{
	for (std::size_t idx = 0; idx < _banList.size(); idx += 1) {
		if (_banList[idx] == user)
			return (true);
	}
	return (false);
}

void	Channel::addBanList(User *user)
{
	if (!isBanList(user))
		_banList.push_back(user);
}

void	Channel::deleteBanList(User *user)
{
	if (!isBanList(user))
		return ;
	for (std::vector<User*>::const_iterator it = _banList.begin(); it != _banList.end(); it++) {
		if (*it == user)
			return ((void)_banList.erase(it));
	}
}

//  Banned Exception Mask :
//  ----------------------------------------------------

std::vector<User*>	Channel::getExcepList(void) const { return (_excepList); }

bool	Channel::isExcepList(User *user) const
{
	for (std::size_t idx = 0; idx < _excepList.size(); idx += 1) {
		if (_excepList[idx] == user)
			return (true);
	}
	return (false);
}

void	Channel::addExcepList(User *user)
{
	if (!isExcepList(user))
		_excepList.push_back(user);
}

void	Channel::deleteExcepList(User *user)
{
	if (!isExcepList(user))
		return ;
	for (std::vector<User*>::const_iterator it = _excepList.begin(); it != _excepList.end(); it++) {
		if (*it == user)
			return ((void)_excepList.erase(it));
	}
}

//  Invite only Mask :
//  ----------------------------------------------------

std::vector<User*>	Channel::getInviteList(void) const { return (_inviteList); }

bool	Channel::isInviteList(User *user) const
{
	for (std::size_t idx = 0; idx < _inviteList.size(); idx += 1) {
		if (_inviteList[idx] == user)
			return (true);
	}
	return (false);
}

void	Channel::addInviteList(User *user)
{
	if (!isInviteList(user))
		_inviteList.push_back(user);
}

void	Channel::deleteInviteList(User *user)
{
	if (!isInviteList(user))
		return ;
	for (std::vector<User*>::const_iterator it = _inviteList.begin(); it != _inviteList.end(); it++) {
		if (*it == user)
			return ((void)_inviteList.erase(it));
	}
}

//  Everything else :
//  ----------------------------------------------------

std::string	Channel::getUsersList(void)
{
	std::stringstream ss;
	std::vector<User*>::iterator begin = _users.begin();
	std::vector<User*>::iterator end = _users.end();
	for (; begin != end; begin++)
	{
		User* user = (*begin);
		if (user == NULL) continue;
		if (isOperator(user)) ss << "@";
		ss << user->getNickname() << " ";
	}
	return ss.str();
}


