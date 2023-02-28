/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:03:13 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/23 10:03:07 by psaulnie         ###   ########.fr       */
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

void Server::iMode(Channel &cChannel, bool set)
{
	cChannel.setMode('i', set);
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

void Server::lMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	std::cout << "----------------HOHO----------------\n";
	cChannel.setMode('l', set);
	for (int i = 0; modeArg[i]; i++) //if mode argument is not valid, displays an error
	{
		std::cout << "I'm in l mode, in for\n";
		if (!isdigit(modeArg[i]))
		{
			std::cout << cUser.getNick() << " " << modeArg << "is not valid\n";
			return;
		}
	}
	if (!modeArg.empty() && set)
	{
		std::cout << "SET limited user connection\n";
		cChannel.setUsrNbMax(static_cast<unsigned short>(std::strtoul(modeArg.c_str(), NULL, 0)));
	}
	else
	{
		std::cout << "MAX CONNECTION -\n";
		cChannel.setUsrNbMax(MAX_CONNECTIONS);
	}
}

void Server::mMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'm';

	cChannel.setMode(mode, set);
}

void Server::nMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'n';

	cChannel.setMode(mode, set);
}

void Server::oMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	if (set)
	{
		std::vector<User> chanUsers = cChannel.getUsers();
		for (std::vector<User>::iterator itUser = chanUsers.begin(); itUser != chanUsers.end(); itUser++)
		{
			if (itUser->getNick() == modeArg)
			{
				itUser->addOpChannel(cChannel);
				cChannel.addOpUser(*itUser);
			}
		}
		chanUsers.clear();
	}
	else
	{
		std::vector<User> chanUsers = cChannel.getUsers();
		for (std::vector<User>::iterator itUser = chanUsers.begin(); itUser != chanUsers.end(); itUser++)
		{
			if (itUser->getNick() == modeArg)
			{
				itUser->removeOpChannel(cChannel);
				cChannel.removeOpUser(*itUser);
			}
		}
		chanUsers.clear();
	}
}

void	Server::pMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'p';

}

void Server::tMode(Channel &cChannel, bool set)
{
	cChannel.setMode('t', set);
}

void	Server::vMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	char mode = 'v';

	cUser.setMode(mode, set);
	if (set)
	{
		for (std::vector<User>::iterator itUser = _clients.begin(); itUser != _clients.end(); itUser++)
		{
			if (modeArg == itUser->getNick())
			{
				itUser->addVoicedChan(cChannel);
				return;
			}
		}
	}
	else
	{
		for (std::vector<User>::iterator itUser = _clients.begin(); itUser != _clients.end(); itUser++)
		{
			if (modeArg == itUser->getNick())
			{
				itUser->removeVoicedChannel(cChannel);
				return;
			}
		}
	}
}
