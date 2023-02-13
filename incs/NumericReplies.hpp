/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:31:44 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/13 15:38:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLIES_HPP
# define NUMERICREPLIES_HPP

#include "SocketIO.hpp"

#define MAX_CONNECTIONS	1024

class	SocketIO;

# define USERMODE_CHARLIST "iswo"
# define CHANNELMODE_CHARLIST "opsitnmlbvk"
# define NR_ARG int const &fd, const std::string& cNick

#include <ctime>
#include <sstream>

class Rep
{
	private:
		std::stringstream	output;
		SocketIO	&io;
	public:
		Rep(SocketIO &io);
		/* Replies */
		void R001(NR_ARG);
		void R002(NR_ARG, const std::string& servName, const std::string &servVersion);
		void R003(NR_ARG, const std::string& date);
		void R004(NR_ARG);

		void R211(NR_ARG, const std::string& infostr); //RPL_STATSLINKINFO
		void R212(NR_ARG, const std::string& infostr); //RPL_STATSCOMMANDS
		void R219(NR_ARG, const std::string& letters); //RPL_ENDOFSTATS
		void R242(NR_ARG, const std::string& infostr); //RPL_STATSUPTIME
		void R243(NR_ARG, const std::string& infostr); //RPL_STATSOLINE

		void R221(NR_ARG, const std::string& modes);

		void R251(NR_ARG, const std::string& infostr);
		void R252(NR_ARG, int ops);
		void R253(NR_ARG, int unknownConnnections);
		void R254(NR_ARG, int channels);
		void R255(NR_ARG, const std::string& infostr);
		void R265(NR_ARG, int users);
		void R266(NR_ARG, int users);

		void R311(NR_ARG, const std::string& queryNick, const std::string& queryName, const std::string& queryRealName);
		void R313(NR_ARG, const std::string& queryNick);
		void R315(NR_ARG, const std::string& name);
		void R318(NR_ARG, const std::string& queryList);
		void R319(NR_ARG, const std::string& queryNick, char prefix, const std::string& chanName);
		void	R322(NR_ARG, int nuser, const std::string& topic, const std::string& ChanName);
		void	R323(NR_ARG);

		void R324(NR_ARG, const std::string& chanName, const std::string& chanModeStr, const std::string& chanModeArgs);

		void R331(NR_ARG, const std::string& chanName);
		void R332(NR_ARG, const std::string& chanName, const std::string& topic);
		void R333(NR_ARG, const std::string& chanName, const std::string& setterNick, time_t timestamp);

		void R341(NR_ARG, const std::string& otherNick, const std::string& chanName);

		void R352(NR_ARG, const std::string& message);

		void R353(NR_ARG, const std::string& chanName, const std::string& nick, char chanPrefix, char userPrefix);
		void R366(NR_ARG, const std::string& chanName);

		void R367(NR_ARG, const std::string& chanName, const std::string& bannedUser);
		void R368(NR_ARG, const std::string& chanName);

		void	R375(NR_ARG, const std::string& serverName);
		void	R372(NR_ARG, const std::string& Motd);
		void	R376(NR_ARG);

		void R381(NR_ARG);

		void R391(NR_ARG, const std::string& servName);

		/* Errors */
		void E401(NR_ARG, const std::string& inputNick);
		void E403(NR_ARG, const std::string& chanName);
		void E404(NR_ARG, const std::string& chanName);

		void E411(NR_ARG, const std::string& cmd);
		void E412(NR_ARG);

		void E421(NR_ARG, const std::string& cmd);

		void E422(NR_ARG);

		void E431(NR_ARG);
		void E432(NR_ARG, const std::string& badNick);
		void E433(NR_ARG, const std::string& badNick);

		void E441(NR_ARG, const std::string& chanName, const std::string& inputNick);
		void E442(NR_ARG, const std::string& chanName);
		void E443(NR_ARG, const std::string& chanName, const std::string& inputNick);

		void E451(NR_ARG);
		void E461(NR_ARG, const std::string& cmd);
		void E462(NR_ARG);
		void E464(NR_ARG);
		void E465(NR_ARG);

		void E471(NR_ARG, const std::string& chanName);
		void E472(NR_ARG, const std::string& modeChar);
		void E473(NR_ARG, const std::string& chanName);
		void E474(NR_ARG, const std::string& chanName);
		void E475(NR_ARG, const std::string& chanName);
		/* For some ungodly reason, ERR_BADCHANMASK doesn't take the user nick as input, still needs a string tho so it's fine */
		void E476(NR_ARG);

		void E482(NR_ARG, const std::string& chanName);

		void E501(NR_ARG);
		void E502(NR_ARG);

		void	clearBuffer();
};

#endif