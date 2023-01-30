/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:31:10 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/30 13:57:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/NumericReplies.hpp"

// void Rep::R001(Server& io, const std::string& cNick)
// {
// 	io << "001 " << cNick << " :Welcome to the Internet Relay Network " << cNick;
// 	io.Send();
// }

// void Rep::R002(Server& io, const std::string& cNick, const std::string& servName, const std::string &servVersion)
// {
// 	io << "002 " << cNick << " :Your host is " << servName << ", running version " << servVersion;
// 	io.Send();
// }

// void Rep::R003(Server& io, const std::string& cNick, const std::string& date)
// {
// 	io << "003 " << cNick << " :This server was created " << date;
// 	io.Send();
// }

// void Rep::R004(Server& io, const std::string& cNick)
// {
// 	/* User modes https://www.rfc-editor.org/rfc/rfc2812#section-3.1.5 */
// 	/* Channel modes https://www.rfc-editor.org/rfc/rfc2811#section-4 */
// 	io << "004 " << cNick << " 42ircserv 1.0 " << CHANNELMODE_CHARLIST << " " << USERMODE_CHARLIST;
// 	io.Send();
// }

// void Rep::R211(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "211 " << cNick << " " << infostr;
// 	io.Send();
// }

// void Rep::R212(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "212 " << cNick << " " << infostr << " 0 0";
// 	io.Send();
// }
// void Rep::R219(Server& io, const std::string& cNick, const std::string& letters)
// {
// 	io << "219 " << cNick << " " << letters << " :End of STATS report";
// 	io.Send();
// }
// void Rep::R242(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "242 " << cNick << " :" << infostr;
// 	io.Send();
// }
// void Rep::R243(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "243 " << cNick << " " << infostr;
// 	io.Send();
// }

// void Rep::R221(Server& io, const std::string& cNick, const std::string& modes)
// {
// 	io << "221 " << cNick << " " << modes;
// 	io.Send();
// }

// void Rep::R251(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "251 " << cNick << " " << infostr;
// 	io.Send();
// }

// void Rep::R252(Server& io, const std::string& cNick, int ops)
// {
// 	io << "252 " << cNick << " " << ops << " :operator(s) online";
// 	io.Send();
// }

// void Rep::R253(Server& io, const std::string& cNick, int unknownConnnections)
// {
// 	io << "253 " << cNick << " " << unknownConnnections << " :unknown connection(s)";
// 	io.Send();
// }

// void Rep::R254(Server& io, const std::string& cNick, int channels)
// {
// 	io << "254 " << cNick << " " << channels << " :channel(s) currently open";
// 	io.Send();
// }

// void Rep::R255(Server& io, const std::string& cNick, const std::string& infostr)
// {
// 	io << "255 " << cNick << " " << infostr;
// 	io.Send();
// }

// void Rep::R265(Server& io, const std::string& cNick, int users)
// {
// 	io << "265 " << cNick << " " << users << " " << MAXCLIENTS <<" :Current local users " << users << ", max " << MAXCLIENTS;
// 	io.Send();
// }

// void Rep::R266(Server& io, const std::string& cNick, int users)
// {
// 	io << "266 " << cNick << " " << users << " " << MAXCLIENTS <<" :Current global users " << users << ", max " << MAXCLIENTS;
// 	io.Send();
// }

// void Rep::R311(Server& io, const std::string& cNick, const std::string& queryNick, const std::string& queryName, const std::string& queryRealName)
// {
// 	io << "311 " << cNick << " " << queryNick << " " << queryName << " * * :" << queryRealName;
// 	io.Send();
// }

// void Rep::R313(Server& io, const std::string& cNick, const std::string& queryNick)
// {
// 	io << "313 " << cNick << " " << queryNick << " :Is an IRC operator";
// 	io.Send();
// }

// void Rep::R315(Server& io, const std::string& cNick, const std::string& name)
// {
// 	io << "315 " << cNick << " " << name << " :End of Who query";
// 	io.Send();
// }

// void Rep::R318(Server& io, const std::string& cNick, const std::string& queryList)
// {
// 	io << "318 " << cNick << " " << queryList << " :End of /WHOIS list";
// 	io.Send();
// }

// void Rep::R319(Server& io, const std::string& cNick, const std::string& queryNick, char prefix, const std::string& chanName)
// {
// 	io << "319 " << cNick << " " << queryNick << " :";
// 	if (prefix != 'u')
// 	 	io << prefix;
// 	io << chanName;
// 	io.Send();
// }

// void Rep::R324(Server& io, const std::string& cNick, const std::string& chanName, const std::string& chanModeStr, const std::string& chanModeArgs)
// {
// 	io << "324 " << cNick << " " << chanName << " " << chanModeStr << " " << chanModeArgs;
// 	io.Send();
// }

// void	Rep::R322(Server& io, const std::string& cNick, int nuser, const std::string& topic, const std::string& chanName)
// {
// 	io << "322 " << cNick << " " << chanName << " " << nuser << " :" << topic;
// 	io.Send();
// }

// void	Rep::R323(Server& io, const std::string& cNick)
// {
// 	io << "323 " << cNick << " :End of LIST";
// 	io.Send();
// }

// void Rep::R331(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "331 " << cNick << " " << chanName << " :No topic set";
// 	io.Send();
// }

// void Rep::R332(Server& io, const std::string& cNick, const std::string& chanName, const std::string& topic)
// {
// 	io << "332 " << cNick << " " << chanName << " :" << topic;
// 	io.Send();
// }

// void Rep::R333(Server& io, const std::string& cNick, const std::string& chanName, const std::string& setterNick, time_t timestamp)
// {
// 	io << "333 " << cNick << " " << chanName << " " << setterNick << " " << timestamp;
// 	io.Send();
// }

// void Rep::R341(Server& io, const std::string& cNick, const std::string& otherNick, const std::string& chanName)
// {
// 	io << "341 " << cNick << " " << otherNick << " " << chanName;
// 	io.Send();
// }

// void Rep::R352(Server& io, const std::string& cNick, const std::string& message)
// {
// 	io << "352 " << cNick << " " << message;
// 	io.Send();
// }

// void Rep::R353(Server& io, const std::string& cNick, const std::string& chanName, const std::string& nick, char chanPrefix, char userPrefix)
// {
// 	if (userPrefix == 'u')
// 		io << "353 " << cNick << " " << chanPrefix << " " << chanName << " :" << nick;
// 	else
// 		io << "353 " << cNick << " " << chanPrefix << " " << chanName << " :" << userPrefix << nick;
// 	io.Send();
// }

// void Rep::R366(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "366 " << cNick << " " << chanName << " :End of NAMES list";
// 	io.Send();
// }

// void Rep::R367(Server& io, const std::string& cNick, const std::string& chanName, const std::string& bannedUser)
// {
// 	io << "367 " << cNick << " " << chanName << " " + bannedUser;
// 	io.Send();
// }

// void Rep::R368(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "368 " << cNick << " " << chanName << " :End of channel ban list";
// 	io.Send();
// }

// void	Rep::R372(Server& io, const std::string& cNick, const std::string& Motd)
// {
// 	io << "372 " << cNick << " :" << Motd;
// 	io.Send();
// }

// void	Rep::R375(Server& io, const std::string& cNick, const std::string& serverName)
// {
// 	io << "375 " << cNick << " :- " << serverName << " Message of the day - ";
// 	io.Send();
// }

// void	Rep::R376(Server& io, const std::string& cNick)
// {
// 	io << "376 " << cNick << " :End of /MOTD command.";
// 	io.Send();
// }

// void	Rep::R381(Server& io, const std::string& cNick)
// {
// 	io << "381 " << cNick << " " << " :You are now an IRC operator";
// 	io.Send();
// }

// void Rep::R391(Server& io, const std::string& cNick, const std::string& servName)
// {
// 	char date_string[128];
// 	time_t curr_time;
// 	tm *curr_tm;
// 	std::time(&curr_time);
// 	curr_tm = std::localtime(&curr_time);

// 	std::strftime(date_string, 50, "%c", curr_tm);

// 	io << "391 " << cNick << " " << servName << " :" << date_string;
// 	io.Send();
// }

// /* Errors */
// void Rep::E401(Server& io, const std::string& cNick, const std::string& inputNick)
// {
// 	io << "401 " << cNick << " " << inputNick << " :No such nick/channel";
// 	io.Send();
// }

// void Rep::E403(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "403 " << cNick << " " << chanName << " :No such channel";
// 	io.Send();
// }

// void Rep::E404(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "404 " << cNick << " " << chanName << " :Cannot send to channel";
// 	io.Send();
// }

// void Rep::E411(Server& io, const std::string& cNick, const std::string& cmd)
// {
// 	io << "411 " << cNick << " :No recipient given (" << cmd << ")";
// 	io.Send();
// }

// void Rep::E412(Server& io, const std::string& cNick)
// {
// 	io << "412 " << cNick << " :No text to send";
// 	io.Send();
// }

// void Rep::E421(Server& io, const std::string& cNick, const std::string& cmd)
// {
// 	io << "421 " << cNick << " " << cmd << " :Unknown command";
// 	io.Send();
// }

// void Rep::E422(Server& io, const std::string& cNick)
// {
// 	io << "422 " << cNick << " :No MOTD in config File";
// 	io.Send();
// }

// void Rep::E431(Server& io, const std::string& cNick)
// {
// 	io << "431 " << cNick << " :No nickname given";
// 	io.Send();
// }

// void Rep::E432(Server& io, const std::string& cNick, const std::string& badNick)
// {
// 	io << "432 " << cNick << " " << badNick << " :Erronous nickname";
// 	io.Send();
// }

// void Rep::E433(Server& io, const std::string& cNick, const std::string& badNick)
// {
// 	io << "433 " << cNick << " " << badNick << " :Nickname is already in use";
// 	io.Send();
// }

// void Rep::E441(Server& io, const std::string& cNick, const std::string& chanName, const std::string& inputNick)
// {
// 	io << "441 " << cNick << " " << inputNick << " " << chanName << " :They aren't on that channel";
// 	io.Send();
// }

// void Rep::E442(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "442 " << cNick << " " << chanName << " :You're not on that channel";
// 	io.Send();
// }

// void Rep::E443(Server& io, const std::string& cNick, const std::string& chanName, const std::string& inputNick)
// {
// 	io << "443 " << cNick << " " << inputNick << " " << chanName << " :Is already on channel";
// 	io.Send();
// }

// void Rep::E451(Server& io, const std::string& cNick)
// {
// 	io << "451 " << cNick << " :You have not registered";
// 	io.Send();
// }

// void Rep::E461(Server& io, const std::string& cNick, const std::string& cmd)
// {
// 	io << "461 " << cNick << " " << cmd << " :Not enough parameters";
// 	io.Send();
// }

// void Rep::E462(Server& io, const std::string& cNick)
// {
// 	io << "462 " << cNick << " :Unauthorized command (already registered)";
// 	io.Send();
// }

// void Rep::E464(Server& io, const std::string& cNick)
// {
// 	io << "464 " << cNick << " :Password incorrect";
// 	io.Send();
// }

// void Rep::E465(Server& io, const std::string& cNick)
// {
// 	io << "465 " << cNick << " :You are banned from this server";
// 	io.Send();
// }

// void Rep::E471(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "471 " << cNick << " " << chanName << " :Cannot join channel (+l)";
// 	io.Send();
// }

// void Rep::E472(Server& io, const std::string& cNick, const std::string& modeChar)
// {
// 	io << "472 " << cNick << " " << modeChar << " :is unknown mode char to me";
// 	io.Send();
// }

// void Rep::E473(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "473 " << cNick << " " << chanName << " :Cannot join channel (+i)";
// 	io.Send();
// }

// void Rep::E474(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "474 " << cNick << " " << chanName << " :Cannot join channel (+b)";
// 	io.Send();
// }

// void Rep::E475(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "475 " << cNick << " " << chanName << " :Cannot join channel (+k)";
// 	io.Send();
// }

// void Rep::E476(Server& io, const std::string& cNick)
// {
// 	io << "476 " << cNick << " :Bad Channel Mask";
// 	io.Send();
// }

// void Rep::E482(Server& io, const std::string& cNick, const std::string& chanName)
// {
// 	io << "482 " << cNick << " " << chanName << " :You're not channel operator";
// 	io.Send();
// }

// void Rep::E501(Server& io, const std::string& cNick)
// {
// 	io << "501 " << cNick << " :Unknown MODE flag";
// 	io.Send();
// }

// void Rep::E502(Server& io, const std::string& cNick)
// {
// 	io << "502 " << cNick << " :Can't view or change mode for other users";
// 	io.Send();
// }