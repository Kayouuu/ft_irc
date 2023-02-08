/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:48:09 by dbouron           #+#    #+#             */
/*   Updated: 2023/02/07 16:48:09 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * invite <channelName> <nickename> : invite a user in a channel with invitation mode (mode +i)
 * @param input
 * @param fd
 * @param cUser
 */
void Server::inviteCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
	for (std::vector<Channel>::iterator it = _channels.begin(); it < _channels.end(); it++)
	{
		if (it->getName() == input[1])
		{
			if (!it->isMode('i'))
				throw std::exception(); //error msg: channel <input[1]> is not in invite mode (+i)
			//user is op ?
			if (!it->isOpUser(cUser))
				_rep.E482(fd, cUser.getNick(), it->getName()); // ERR_CHANOPRIVSNEEDED
			//nickname is registered in server ?
			for (std::vector<User>::iterator ite = _clients.begin(); ite < _clients.end(); ite++)
			{
				if (ite->getNick() == input[2])
				{
					it->addUser(*ite);
					_rep.R341(fd, cUser.getNick(), ite->getNick(), it->getName()); // RPL_INVITING
					return ;
				}
			}
			_rep.E401(fd, cUser.getNick(), input[2]); // ERR_NOSUCHNICK/CHANNEL
		}
	}
	_rep.E401(fd, cUser.getNick(), input[1]); // ERR_NOSUCHNICK/CHANNEL
}

//ERR_NEEDMOREPARAMS (E461)
//ERR_NOTONCHANNEL (E442)
//ERR_USERONCHANNEL (E443)
