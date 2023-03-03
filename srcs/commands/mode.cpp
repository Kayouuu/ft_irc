/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:47:31 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/03 10:27:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::notAMode(std::string const &which, std::string const &input, User &cUser)
{
	for (int j = 1; input[j]; j++)
		if (!isalpha(input[j]))
			_rep.E472(cUser.getFd(), cUser.getNick(), input[j]);
	if (which == "channel")
	{
		for (int i = 1; input[i]; i++)
		{
			if (input[i] != 'k' || input[i] != 'l' || input[i] != 'm'
					|| input[i] != 'n' || input[i] != 'o' || input[i] != 'p'
					|| input[i] != 't' || input[i] != 'v')
				_rep.E501(cUser.getFd(), cUser.getNick());
		}
	}
	else if (which == "user")
	{
		for (int i = 1; input[i]; i++)
		{
			if (input[i] != 'o' || input[i] != 'v')
				_rep.E501(cUser.getFd(), cUser.getNick());
		}
	}
}

/**
 * Change mode for a channel:	/MODE <channelName> <+|-> <mode> [parametres]
 * Change mode for a user:		/MODE <nickname> <+|-> <mode>
 * @param input
 * @param fd
 * @param cUser
 */
void	Server::modeCmd(std::vector<std::string> &input, User &cUser)
{
	if (input[1].empty() || input[2].empty())
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]); // ERR_NEEDMOREPARAMS
		return;
	}
	if (input[1][0] == '#') // Mode for a channel
	{
		//	If <modestring> is not given, the RPL_CHANNELMODEIS (324) numeric is returned.
		std::vector<Channel>::iterator	itChan;
		for (itChan = _channels.begin(); itChan != _channels.end(); itChan++)
			if (itChan->getName() == input[1])
				break ;
		std::cout << RED << itChan->getName() << NO_COLOR << std::endl;
		if (itChan == _channels.end())
		{
			_rep.E403(cUser.getFd(), cUser.getNick(), input[1]); // TOCHECK if enough + if need to substr the '#' from input[1]
			return ;
		}
		if (!itChan->isUser(cUser))
		{
			// TODO remove
			// std::vector<User> test = itChan->getUsers();
			// for (std::vector<User>::iterator TEST = test.begin(); TEST != test.end(); TEST++) {
			// 	std::cout << GREEN << TEST->getNick() << NO_COLOR << std::endl;
			// }
			_rep.E442(cUser.getFd(), cUser.getNick(), input[1]);
			return ;
		}
		if (!itChan->isOpUser(cUser))
		{
			_rep.E482(cUser.getFd(), cUser.getNick(), input[1]);
			return ;
		}
		if ((input[2][0] != '+' && input[2][0] != '-') || input[2].length() < 2) // TOCHECK
		{
			_rep.R324(cUser.getFd(), cUser.getNick(), input[1], input[2], input[3]);
			return ;
		}
		notAMode("channel", input[2], cUser);
		
		bool	set = false;
		if (input[2][0] == '+')
			set = true;
		for (int i = 1; input[2][i]; i++)
		{
			modeHandler(cUser, *itChan, input[2][i], input, set);
		}
	}
	else // Mode for an user
	{
		//	If <target> is a nickname that does not exist on the network,
		//	the ERR_NOSUCHNICK (401) numeric is returned.
		std::vector<User>::iterator user = _clients.begin();
		for (user; user < _clients.end(); user++)
		{
			if (user->getNick() == input[1])
			{
				//	If <target> is a different nick than the user who sent the command,
				//	the ERR_USERSDONTMATCH (502) numeric is returned.
				if (cUser.getNick() != user->getNick())
				{
					_rep.E502(cUser.getFd(), cUser.getNick());
					return;
				}
				//	If <modestring> is not given,
				//	the RPL_UMODEIS (221) numeric is sent back containing the current modes of the target user.
				if (input[2][0] != '+' || input[2][0] != '-')
				{
					_rep.R221(cUser.getFd(), cUser.getNick(), cUser.getModes());
					return ;
				}

				notAMode("user", input[2], cUser);

				if (input[2][0] == '+')
				for (int i = 1; input[2][i]; i++)
				{
					modeHandlerUser(cUser.getFd(), input[2], cUser, input[2][i]);
					return;
				}
			}
		}
		_rep.E401(cUser.getFd(), cUser.getNick(), input[1]);
		//	If <modestring> is given, the supplied modes will be applied,
		//	and a MODE message will be sent to the user containing the changed modes.
		//	If one or more modes sent are not implemented on the server,
		//	the server MUST apply the modes that are implemented,
		//	and then send the ERR_UMODEUNKNOWNFLAG (501) in reply along with the MODE message.
	}
}

void	Server::modeHandler(User &cUser, Channel &cChannel, char &mode, std::vector<std::string> &input, bool set)
{
	switch(mode)
	{
		case 'b':
			bMode(cUser, cChannel, input[3], set);
			break ;
		case 'i':
			iMode(cChannel, set);
			break ;
		case 'k':
			kMode(cUser, cChannel, input[3], set);
			break ;
		case 'l':
			lMode(cUser, cChannel, input[3], set);
			break ;
		case 'm':
			mMode(cUser, cChannel, set);
			break ;
		case 'n':
			nMode(cUser, cChannel, input[3], set);
			break ;
		case 'o':
			oMode(cUser, cChannel, input[3], set);
			break ;
		case 't':
			tMode(cChannel, set);
			break ;
		case 'v':
			vMode(cUser, cChannel, input[3], set);
			break ;
		default:
			return ;
	}
	_rep.R324(cUser.getFd(), cUser.getNick(), input[1], input[2], input[3]);
	for (int i = 0; i < 4; i++)
		input[i].clear();
}

void	Server::modeHandlerUser(int fd, std::string &input, User &cUser, char &mode)
{
	switch(mode)
	{
		case 'o':
			oMode(fd, input, cUser);
			break ;
		default:
			return ;
	}
}

void Server::oMode(int fd, std::string &input, User &cUser)
{
	int i = 0;
	if (input[i] == '-')
		cUser.setMode('o', false);
	_rep.R221(cUser.getFd(), cUser.getNick(), cUser.getModes());
}
