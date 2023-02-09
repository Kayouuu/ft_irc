/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:31:10 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/09 14:30:02 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/NumericReplies.hpp"

Rep::Rep(SocketIO &io) : io(io) { }

void Rep::R001(int const &fd, const std::string &cNick)
{
	output = "001 " + cNick + " :Welcome " + cNick + " to the Internet Chat Relay!\r\n";
	io.emit(output, fd);
}

void Rep::R002(int const &fd, const std::string &cNick, const std::string& servName, const std::string &servVersion)
{
	output = "002 " + cNick + " :Your host is " + servName + ", running version " + servVersion + "\r\n";
	io.emit(output, fd);
}

void Rep::R003(int const &fd, const std::string &cNick, const std::string& date)
{
	output = "003 " + cNick + " :This server was created " + date + "\r\n";
	io.emit(output, fd);
}

// void Rep::R004(int const &fd, const std::string &cNick)
// {
// 	/* User modes https://www.rfc-editor.org/rfc/rfc2812#section-3.1.5 */
// 	/* Channel modes https://www.rfc-editor.org/rfc/rfc2811#section-4 */
// 	output = "004 " + cNick + " 42ircserv 1.0 " + CHANNELMODE_CHARLIST + " " + USERMODE_CHARLIST;
// 	io.emit(output, fd);
// }

void Rep::R211(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "211 " + cNick + " " + infostr;
	io.emit(output, fd);
}

void Rep::R212(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "212 " + cNick + " " + infostr + " 0 0";
	io.emit(output, fd);
}
void Rep::R219(int const &fd, const std::string &cNick, const std::string& letters)
{
	output = "219 " + cNick + " " + letters + " :End of STATS report";
	io.emit(output, fd);
}
void Rep::R242(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "242 " + cNick + " :" + infostr;
	io.emit(output, fd);
}
void Rep::R243(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "243 " + cNick + " " + infostr;
	io.emit(output, fd);
}

void Rep::R221(int const &fd, const std::string &cNick, const std::string& modes)
{
	output = "221 " + cNick + " " + modes;
	io.emit(output, fd);
}

void Rep::R251(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "251 " + cNick + " " + infostr;
	io.emit(output, fd);
}

// void Rep::R252(int const &fd, const std::string &cNick, int ops)
// {
// 	output = "252 " + cNick + " " + ops + " :operator(s) online";
// 	io.emit(output, fd);
// }

// void Rep::R253(int const &fd, const std::string &cNick, int unknownConnnections)
// {
// 	output = "253 " + cNick + " " + unknownConnnections + " :unknown connection(s)";
// 	io.emit(output, fd);
// }

// void Rep::R254(int const &fd, const std::string &cNick, int channels)
// {
// 	output = "254 " + cNick + " " + channels + " :channel(s) currently open";
// 	io.emit(output, fd);
// }

void Rep::R255(int const &fd, const std::string &cNick, const std::string& infostr)
{
	output = "255 " + cNick + " " + infostr;
	io.emit(output, fd);
}

// void Rep::R265(int const &fd, const std::string &cNick, int users)
// {
// 	output = "265 " + cNick + " " + users + " " + MAXCLIENTS +" :Current local users " + users + ", max " + MAXCLIENTS;
// 	io.emit(output, fd);
// }

// void Rep::R266(int const &fd, const std::string &cNick, int users)
// {
// 	output = "266 " + cNick + " " + users + " " + MAXCLIENTS +" :Current global users " + users + ", max " + MAXCLIENTS;
// 	io.emit(output, fd);
// }

void Rep::R311(int const &fd, const std::string &cNick, const std::string& queryNick, const std::string& queryName, const std::string& queryRealName)
{
	output = "311 " + cNick + " " + queryNick + " " + queryName + " * * :" + queryRealName;
	io.emit(output, fd);
}

void Rep::R313(int const &fd, const std::string &cNick, const std::string& queryNick)
{
	output = "313 " + cNick + " " + queryNick + " :Is an IRC operator";
	io.emit(output, fd);
}

void Rep::R315(int const &fd, const std::string &cNick, const std::string& name)
{
	output = "315 " + cNick + " " + name + " :End of Who query";
	io.emit(output, fd);
}

void Rep::R318(int const &fd, const std::string &cNick, const std::string& queryList)
{
	output = "318 " + cNick + " " + queryList + " :End of /WHOIS list";
	io.emit(output, fd);
}

void Rep::R319(int const &fd, const std::string &cNick, const std::string& queryNick, char prefix, const std::string& chanName)
{
	output = "319 " + cNick + " " + queryNick + " :";
	if (prefix != 'u')
	 	output = prefix;
	output = chanName;
	io.emit(output, fd);
}

void Rep::R324(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& chanModeStr, const std::string& chanModeArgs)
{
	output = "324 " + cNick + " " + chanName + " " + chanModeStr + " " + chanModeArgs;
	io.emit(output, fd);
}

// void	Rep::R322(int const &fd, const std::string &cNick, int nuser, const std::string& topic, const std::string& chanName)
// {
// 	output = "322 " + cNick + " " + chanName + " " + nuser + " :" + topic;
// 	io.emit(output, fd);
// }

void	Rep::R323(int const &fd, const std::string &cNick)
{
	output = "323 " + cNick + " :End of LIST";
	io.emit(output, fd);
}

void Rep::R331(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "331 " + cNick + " " + chanName + " :No topic set";
	io.emit(output, fd);
}

void Rep::R332(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& topic)
{
	output = "332 " + cNick + " " + chanName + " :" + topic;
	io.emit(output, fd);
}

// void Rep::R333(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& setterNick, time_t timestamp)
// {
// 	output = "333 " + cNick + " " + chanName + " " + setterNick + " " + timestamp;
// 	io.emit(output, fd);
// }

void Rep::R341(int const &fd, const std::string &cNick, const std::string& otherNick, const std::string& chanName)
{
	output = "341 " + cNick + " " + otherNick + " " + chanName;
	io.emit(output, fd);
}

void Rep::R352(int const &fd, const std::string &cNick, const std::string& message)
{
	output = "352 " + cNick + " " + message;
	io.emit(output, fd);
}

void Rep::R353(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& nick, char chanPrefix, char userPrefix)
{
	if (userPrefix == 'u')
		output = "353 " + cNick + " " + chanPrefix + " " + chanName + " :" + nick;
	else
		output = "353 " + cNick + " " + chanPrefix + " " + chanName + " :" + userPrefix + nick;
	io.emit(output, fd);
}

void Rep::R366(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "366 " + cNick + " " + chanName + " :End of NAMES list";
	io.emit(output, fd);
}

void Rep::R367(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& bannedUser)
{
	output = "367 " + cNick + " " + chanName + " " + bannedUser;
	io.emit(output, fd);
}

void Rep::R368(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "368 " + cNick + " " + chanName + " :End of channel ban list";
	io.emit(output, fd);
}

void	Rep::R372(int const &fd, const std::string &cNick, const std::string& Motd)
{
	output = "372 " + cNick + " :" + Motd;
	io.emit(output, fd);
}

void	Rep::R375(int const &fd, const std::string &cNick, const std::string& serverName)
{
	output = "375 " + cNick + " :- " + serverName + " Message of the day - ";
	io.emit(output, fd);
}

void	Rep::R376(int const &fd, const std::string &cNick)
{
	output = "376 " + cNick + " :End of /MOTD command.";
	io.emit(output, fd);
}

void	Rep::R381(int const &fd, const std::string &cNick)
{
	output = "381 " + cNick + " " + " :You are now an IRC operator";
	io.emit(output, fd);
}

void Rep::R391(int const &fd, const std::string &cNick, const std::string& servName)
{
	char date_string[128];
	time_t curr_time;
	tm *curr_tm;
	std::time(&curr_time);
	curr_tm = std::localtime(&curr_time);

	std::strftime(date_string, 50, "%c", curr_tm);

	output = "391 " + cNick + " " + servName + " :" + date_string;
	io.emit(output, fd);
}

/* Errors */
void Rep::E401(int const &fd, const std::string &cNick, const std::string& inputNick)
{
	output = "401 " + cNick + " " + inputNick + " :No such nick/channel";
	io.emit(output, fd);
}

void Rep::E403(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "403 " + cNick + " " + chanName + " :No such channel";
	io.emit(output, fd);
}

void Rep::E404(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "404 " + cNick + " " + chanName + " :Cannot send to channel";
	io.emit(output, fd);
}

void Rep::E411(int const &fd, const std::string &cNick, const std::string& cmd)
{
	output = "411 " + cNick + " :No recipient given (" + cmd + ")";
	io.emit(output, fd);
}

void Rep::E412(int const &fd, const std::string &cNick)
{
	output = "412 " + cNick + " :No text to send";
	io.emit(output, fd);
}

void Rep::E421(int const &fd, const std::string &cNick, const std::string& cmd)
{
	output = "421 " + cNick + " " + cmd + " :Unknown command";
	io.emit(output, fd);
}

void Rep::E422(int const &fd, const std::string &cNick)
{
	output = "422 " + cNick + " :No MOTD in config File";
	io.emit(output, fd);
}

void Rep::E431(int const &fd, const std::string &cNick)
{
	output = "431 " + cNick + " :No nickname given";
	io.emit(output, fd);
}

void Rep::E432(int const &fd, const std::string &cNick, const std::string& badNick)
{
	output = "432 " + cNick + " " + badNick + " :Erronous nickname";
	io.emit(output, fd);
}

void Rep::E433(int const &fd, const std::string &cNick, const std::string& badNick)
{
	output = "433 " + cNick + " " + badNick + " :Nickname is already in use\r\n";
	io.emit(output, fd);
}

void Rep::E441(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& inputNick)
{
	output = "441 " + cNick + " " + inputNick + " " + chanName + " :They aren't on that channel";
	io.emit(output, fd);
}

void Rep::E442(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "442 " + cNick + " " + chanName + " :You're not on that channel";
	io.emit(output, fd);
}

void Rep::E443(int const &fd, const std::string &cNick, const std::string& chanName, const std::string& inputNick)
{
	output = "443 " + cNick + " " + inputNick + " " + chanName + " :Is already on channel";
	io.emit(output, fd);
}

void Rep::E451(int const &fd, const std::string &cNick)
{
	output = "451 " + cNick + " :You have not registered";
	io.emit(output, fd);
}

void Rep::E461(int const &fd, const std::string &cNick, const std::string& cmd)
{
	output = "461 " + cNick + " " + cmd + " :Not enough parameters\r\n";
	io.emit(output, fd);
}

void Rep::E462(int const &fd, const std::string &cNick)
{
	output = "462 " + cNick + " :Unauthorized command (already registered)\r\n";
	io.emit(output, fd);
}

void Rep::E464(int const &fd, const std::string &cNick)
{
	output = "464 " + cNick + " :Password incorrect";
	io.emit(output, fd);
}

void Rep::E465(int const &fd, const std::string &cNick)
{
	output = "465 " + cNick + " :You are banned from this server";
	io.emit(output, fd);
}

void Rep::E471(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "471 " + cNick + " " + chanName + " :Cannot join channel (+l)";
	io.emit(output, fd);
}

void Rep::E472(int const &fd, const std::string &cNick, const std::string& modeChar)
{
	output = "472 " + cNick + " " + modeChar + " :is unknown mode char to me";
	io.emit(output, fd);
}

void Rep::E473(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "473 " + cNick + " " + chanName + " :Cannot join channel (+i)";
	io.emit(output, fd);
}

void Rep::E474(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "474 " + cNick + " " + chanName + " :Cannot join channel (+b)";
	io.emit(output, fd);
}

void Rep::E475(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "475 " + cNick + " " + chanName + " :Cannot join channel (+k)";
	io.emit(output, fd);
}

void Rep::E476(int const &fd, const std::string &cNick)
{
	output = "476 " + cNick + " :Bad Channel Mask";
	io.emit(output, fd);
}

void Rep::E482(int const &fd, const std::string &cNick, const std::string& chanName)
{
	output = "482 " + cNick + " " + chanName + " :You're not channel operator";
	io.emit(output, fd);
}

void Rep::E501(int const &fd, const std::string &cNick)
{
	output = "501 " + cNick + " :Unknown MODE flag";
	io.emit(output, fd);
}

void Rep::E502(int const &fd, const std::string &cNick)
{
	output = "502 " + cNick + " :Can't view or change mode for other users";
	io.emit(output, fd);
}
