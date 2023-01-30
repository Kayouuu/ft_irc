/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:31:44 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/30 13:33:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLIES_HPP
# define NUMERICREPLIES_HPP

#include "Server.hpp"

# define NR_ARG Server& io, const std::string& cNick
# define NR_IN *io, user->getNick()


class Rep
{
public:
	/* Replies */
	static void R001(NR_ARG);
	static void R002(NR_ARG, const std::string& servName, const std::string &servVersion);
	static void R003(NR_ARG, const std::string& date);
	static void R004(NR_ARG);

	static void R211(NR_ARG, const std::string& infostr); //RPL_STATSLINKINFO
	static void R212(NR_ARG, const std::string& infostr); //RPL_STATSCOMMANDS
	static void R219(NR_ARG, const std::string& letters); //RPL_ENDOFSTATS
	static void R242(NR_ARG, const std::string& infostr); //RPL_STATSUPTIME
	static void R243(NR_ARG, const std::string& infostr); //RPL_STATSOLINE

	static void R221(NR_ARG, const std::string& modes);

	static void R251(NR_ARG, const std::string& infostr);
	static void R252(NR_ARG, int ops);
	static void R253(NR_ARG, int unknownConnnections);
	static void R254(NR_ARG, int channels);
	static void R255(NR_ARG, const std::string& infostr);
	static void R265(NR_ARG, int users);
	static void R266(NR_ARG, int users);

	static void R311(NR_ARG, const std::string& queryNick, const std::string& queryName, const std::string& queryRealName);
	static void R313(NR_ARG, const std::string& queryNick);
	static void R315(NR_ARG, const std::string& name);
	static void R318(NR_ARG, const std::string& queryList);
	static void R319(NR_ARG, const std::string& queryNick, char prefix, const std::string& chanName);
	static void	R322(NR_ARG, int nuser, const std::string& topic, const std::string& ChanName);
	static void	R323(NR_ARG);

	static void R324(NR_ARG, const std::string& chanName, const std::string& chanModeStr, const std::string& chanModeArgs);

	static void R331(NR_ARG, const std::string& chanName);
	static void R332(NR_ARG, const std::string& chanName, const std::string& topic);
	static void R333(NR_ARG, const std::string& chanName, const std::string& setterNick, time_t timestamp);

	static void R341(NR_ARG, const std::string& otherNick, const std::string& chanName);

	static void R352(NR_ARG, const std::string& message);

	static void R353(NR_ARG, const std::string& chanName, const std::string& nick, char chanPrefix, char userPrefix);
	static void R366(NR_ARG, const std::string& chanName);

	static void R367(NR_ARG, const std::string& chanName, const std::string& bannedUser);
	static void R368(NR_ARG, const std::string& chanName);

	static void	R375(NR_ARG, const std::string& serverName);
	static void	R372(NR_ARG, const std::string& Motd);
	static void	R376(NR_ARG);

	static void R381(NR_ARG);

	static void R391(NR_ARG, const std::string& servName);

	/* Errors */
	static void E401(NR_ARG, const std::string& inputNick);
	static void E403(NR_ARG, const std::string& chanName);
	static void E404(NR_ARG, const std::string& chanName);

	static void E411(NR_ARG, const std::string& cmd);
	static void E412(NR_ARG);

	static void E421(NR_ARG, const std::string& cmd);

	static void E422(NR_ARG);

	static void E431(NR_ARG);
	static void E432(NR_ARG, const std::string& badNick);
	static void E433(NR_ARG, const std::string& badNick);

	static void E441(NR_ARG, const std::string& chanName, const std::string& inputNick);
	static void E442(NR_ARG, const std::string& chanName);
	static void E443(NR_ARG, const std::string& chanName, const std::string& inputNick);

	static void E451(NR_ARG);
	static void E461(NR_ARG, const std::string& cmd);
	static void E462(NR_ARG);
	static void E464(NR_ARG);
	static void E465(NR_ARG);

	static void E471(NR_ARG, const std::string& chanName);
	static void E472(NR_ARG, const std::string& modeChar);
	static void E473(NR_ARG, const std::string& chanName);
	static void E474(NR_ARG, const std::string& chanName);
	static void E475(NR_ARG, const std::string& chanName);
	/* For some ungodly reason, ERR_BADCHANMASK doesn't take the user nick as input, still needs a string tho so it's fine */
	static void E476(NR_ARG);

	static void E482(NR_ARG, const std::string& chanName);

	static void E501(NR_ARG);
	static void E502(NR_ARG);
};

#endif