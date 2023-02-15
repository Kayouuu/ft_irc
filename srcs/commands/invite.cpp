/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:48:09 by dbouron           #+#    #+#             */
/*   Updated: 2023/02/13 10:20:13 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * invite <channelName> <nickename> : invite a user in a channel with invitation mode (mode +i)
 * @param input
 * @param fd
 * @param cUser
 */
void Server::inviteCmd(std::vector<std::string> &input, int fd, User &cUser)
{
	if (input[1].empty() || input[2].empty())
	{
		_rep.E461(fd, cUser.getNick(), input[0]); // ERR_NEEDMOREPARAMS
		return;
	}
	for (std::vector<Channel>::iterator chan = _channels.begin(); chan < _channels.end(); chan++)
	{
		if (chan->getName() == input[1])
		{
			//channel is on invite mode +i ?
			if (!chan->isMode('i'))
				throw std::exception(); //error msg: channel <input[1]> is not in invite mode (+i)

			//user is on channel ?
			if (!chan->isUser(cUser))
			{
				_rep.E442(fd, cUser.getNick(), chan->getName()); // ERR_NOTONCHANNEL
				return ;
			}

			//user is op ?
			if (!chan->isOpUser(cUser))
			{
				_rep.E482(fd, cUser.getNick(), chan->getName()); // ERR_CHANOPRIVSNEEDED
				return;
			}

			//nickname is registered in server ?
			for (std::vector<User>::iterator user = _clients.begin(); user < _clients.end(); user++)
			{
				if (user->getNick() == input[2])
				{
					//is nickname already on channel ?
					if (chan->isUser(*user))
					{
						_rep.E443(fd, cUser.getNick(), chan->getName(), user->getNick()); // ERR_USERONCHANNEL
						return ;
					}
					chan->addUser(*user);
					_rep.R341(fd, cUser.getNick(), user->getNick(), chan->getName()); // RPL_INVITING
					return ;
				}
			}
			_rep.E401(fd, cUser.getNick(), input[2]); // ERR_NOSUCHNICK
			return ;
		}
	}
	_rep.E403(fd, cUser.getNick(), input[1]); // ERR_NOSUCHCHANNEL
}
