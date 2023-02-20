/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:03:13 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/20 14:32:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

void	Server::bMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	// TODO send banlist ??
	char mode = 'b';
	std::vector<User>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->getNick() == modeArg)
			break ;
	}
	if (it != _clients.end())
	{
		it->setMode(mode, set);
		if (set == true)
		{
			cChannel.banUser(*it);
			it->setMode(mode, set);
			_rep.E474(it->getFd(), it->getNick(), cChannel.getName());
		}
		else
		{
			cChannel.unbanUser(*it);
			it->setMode(mode, set);
			// TOCHECK if need to send error msg
		}
	}
	else
	{
		// TODO user not found
		// RPL_BANLIST
		// RPL_ENDBANLIST
	}
}

void	Server::iMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'i';

}

void	Server::kMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'k';

	cChannel.setMode(mode, set);
	if (set == true)
		cChannel.setPw(modeArg);
	else
		cChannel.setPw("");
	
}

void	Server::lMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'l';

}

void	Server::mMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'm';

	cChannel.setMode(mode, set);
}

void	Server::nMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'n';

}

void	Server::oMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'o';

}

void	Server::pMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'p';

}

void	Server::tMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 't';

}

void	Server::vMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'v';

	cUser.setMode(mode, set);
}