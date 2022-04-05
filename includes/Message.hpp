/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:49:09 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/25 15:10:52 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#define RPL_WELCOME				"001" // Welcome to the Internet Relay Network
#define RPL_YOURHOST			"002" // Your host is
#define RPL_CREATED				"003" // This server was created
#define RPL_MYINFO				"004" // I have your hostname,servername, and version
#define RPL_UMODEIS				"221" // User mode
#define RPL_USERHOST			"302" // :<nick>=<user>@<host>
#define RPL_MOTDSTART			"375" // :- <server> Message of the day -
#define RPL_MOTD				"372" // :- <text>
#define RPL_ENDOFMOTD			"376" // :End of MOTD command
#define RPL_VERSION				"351" // <version>.<debuglevel> <server> :<comments>
#define RPL_TIME				"391" // :<server> <version> :<comments>
#define RPL_AWAY				"301" // :<nick> :<away message>
#define RPL_UNAWAY				"305" // :You are no longer marked as being away
#define RPL_NOWAWAY				"306" // :You have been marked as being away
#define RPL_LISTSTART			"321" // Channel :Users  Name
#define RPL_LIST				"322" // <channel> <# visible> :<topic>
#define RPL_LISTEND				"323" // :End of LIST
#define RPL_CHANNELMODEIS		"324" // :<channel> <mode> <mode params>
#define RPL_NOTOPIC				"331" // :<channel> :No topic is set
#define RPL_TOPIC				"332" // :<channel> :<topic>
#define RPL_INVITING			"341" // :"<channel> <nick>"
#define RPL_INVITELIST          "346" // :<channel> <invitemask>
#define RPL_ENDOFINVITELIST     "347" // :<channel> :End of channel invite list
#define RPL_EXCEPTLIST          "348" // :<channel> <exceptionmask>
#define RPL_ENDOFEXCEPTLIST     "349" // :<channel> :End of channel exception list
#define RPL_NAMREPLY			"353" // :<channel> <names>
#define RPL_ENDOFNAMES			"366" // :<channel> :End of NAMES list
#define RPL_BANLIST             "367" // :<channel> <banmask>
#define RPL_ENDOFBANLIST        "368" // :<channel> :End of channel ban list
#define RPL_YOUREOPER			"381" // :You are now an IRC operator

#define ERR_NOSUCHNICK			"401" // :<nickname> :No such nick/channel
#define ERR_NOSUCHSERVER		"402" // :<server name> :No such server
#define ERR_NOSUCHCHANNEL		"403" // :<channel name> :No such channel
#define ERR_CANNOTSENDTOCHAN	"404" // :<channel name> :Cannot send to channel
#define ERR_TOOMANYCHANNELS		"405" // :<channel name> :You have joined too many channels
#define ERR_WASNOSUCHNICK		"406" // :<nickname> :There was no such nickname
#define ERR_TOOMANYTARGETS		"407" // :<target> :Duplicate recipients. No message delivered
#define ERR_NOORIGIN			"409" // :No origin specified
#define ERR_NORECIPIENT			"411" // :No recipient given (<command>)
#define ERR_NOTEXTTOSEND		"412" // :No text to send
#define ERR_NOTOPLEVEL			"413" // :No toplevel domain specified
#define ERR_WILDTOPLEVEL		"414" // :Wildcard in toplevel domain
#define ERR_UNKNOWNCOMMAND		"421" // :Unknown command
#define ERR_NOMOTD				"422" // :MOTD File is missing
#define ERR_NOADMININFO			"423" // :No administrative info available
#define ERR_FILEERROR			"424" // :File error doing <file op> on <file>
#define ERR_NONICKNAMEGIVEN		"431" // :No nickname given
#define ERR_ERRONEUSNICKNAME	"432" // :Erroneus nickname
#define ERR_NICKNAMEINUSE		"433" // :Nickname is already in use.
#define ERR_NICKCOLLISION		"436" // :Nickname collision KILL
#define ERR_USERNOTINCHANNEL	"441" // <nick> <channel> :They aren't on that channel
#define ERR_NOTONCHANNEL		"442" // :You're not on that channel
#define ERR_USERONCHANNEL		"443" // :is already on channel
#define ERR_NOLOGIN				"444" // :User not logged in
#define ERR_SUMMONDISABLED		"445" // :SUMMON has been disabled
#define ERR_USERSDISABLED		"446" // :USERS has been disabled
#define ERR_NOTREGISTERED		"451" // :You have not registered
#define ERR_NEEDMOREPARAMS		"461" // <command> :Not enough parameters
#define ERR_ALREADYREGISTRED	"462" // :Unauthorized command (already registered)
#define ERR_PASSWDMISMATCH		"464" // :Password incorrect
#define ERR_KEYSET              "467" // :Channel key already set
#define ERR_CHANNELISFULL		"471" // :Cannot join channel (+l)
#define ERR_UNKNOWNMODE			"472" // :is unknown mode char to me for <channel>
#define ERR_INVITEONLYCHAN		"473" // :Cannot join channel (+i)
#define ERR_BANNEDFROMCHAN		"474" // :Cannot join channel (+b)
#define ERR_BADCHANNELKEY		"475" // :Cannot join channel (+k)
#define ERR_BADCHANMASK			"476" // :Bad Channel Mask
#define ERR_NOCHANMODES			"477" // :Channel doesn't support modes
#define ERR_BANLISTFULL			"478" // :Channel list is full
#define ERR_NOPRIVILEGES		"481" // :Permission Denied- You're not an IRC operator
#define ERR_CHANOPRIVSNEEDED	"482" // :You're not channel operator
#define ERR_RESTRICTED			"484" // :Your connection is restricted
#define ERR_UNIQOPPRIVSNEEDED	"485" // :You must be at least a half-operator to do this
#define ERR_NOOPERHOST			"491" // :No O-lines for your host
#define ERR_UMODEUNKNOWNFLAG	"501" // :Unknown MODE flag
#define ERR_USERSDONTMATCH		"502" // :Cannot change mode for other users
#define ERR_NEEDREGGEDNICK		"671" // :You need a registered nick to do this

#endif
