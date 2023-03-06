/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:03:13 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/06 14:43:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

void	Server::bMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set)
{
	std::vector<User>::iterator itUser;
	for (itUser = _clients.begin(); itUser != _clients.end(); itUser++)
	{
		if (itUser->getNick() == modeArg)
			break ;
	}
	if (itUser != _clients.end())
	{
		itUser->setMode('b', set);
		if (set == true)
		{
			cChannel.banUser(*itUser);
			itUser->setMode('b', set);
			_rep.E474(cUser.getFd(), itUser->getNick(), cChannel.getName());
		}
		else
		{
			cChannel.unbanUser(*itUser);
			itUser->setMode('b', set);
			// TODO check if need to send error msg
		}
	}
	else if (modeArg == "")
		cChannel.listBannedUser(_rep, cUser);
	else
		_rep.E401(cUser.getFd(), cUser.getNick(), modeArg);
	std::vector<std::string> output;
	output.push_back("KICK");
	output.push_back(cChannel.getName());
	output.push_back(modeArg);
	kickCmd(output, cUser);
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
	for (int i = 0; modeArg[i]; i++) // If the mode argument is not valid, displays an error
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

void Server::mMode(User &cUser, Channel &cChannel, bool set)
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
