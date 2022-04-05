#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Utils.hpp"

class KickCommand : public Command
{
	protected:
		Server*	_server;
	
	public:
		KickCommand(Server* sever);
		~KickCommand(void);

		bool onCommand(User* sender, std::vector<std::string> args);
};

#endif