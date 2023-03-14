/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:33:55 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/13 11:34:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * /KICK <channelName> <nickname> [message] (kick a client from a channel)
 * @param input
 * @param fd
 * @param cUser
 */
void Server::kickCmd(std::vector<std::string> &input, User &cUser)
{
	if (input.size() < 3)
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]); // ERR_NEEDMOREPARAMS
		return;
	}
	for (std::vector<Channel>::iterator chan = _channels.begin(); chan < _channels.end(); chan++)
	{
		if (chan->getName() == input[1])
		{
			// Is user on channel ?
			if (!chan->isUser(cUser))
			{
				_rep.E442(cUser.getFd(), cUser.getNick(), chan->getName()); // ERR_NOTONCHANNEL
				return ;
			}

			// Is user op ?
			if (!chan->isOpUser(cUser))
			{
				_rep.E482(cUser.getFd(), cUser.getNick(), chan->getName()); // ERR_CHANOPRIVSNEEDED
				return;
			}

			// Is nickname on channel ?
			std::vector<User> users = chan->getUsers();
			for (std::vector<User>::iterator user = users.begin(); user < users.end(); user++)
			{
				if (user->getNick() == input[2])
				{
					std::vector<User> chanUsers = chan->getUsers();
					std::string userNick;
					std::string msg;
					if (cUser.isChanOp(*chan)) {
						userNick = "@";
					}
					userNick.append(cUser.getNick());
					for (int i = 3; i < input.size(); i++)
					{
						msg.append(input[i]);
						if (i != input.size() - 1)
							msg.append(" ");
					}
					for (std::vector<User>::iterator itChanUser = chanUsers.begin(); itChanUser != chanUsers.end(); itChanUser++)
					{
						emit(":" + userNick + " " + input[0] + " " + chan->getName() + " " + input[2] + " " + msg,itChanUser->getFd());
					}
					chan->removeUser(*user);
					return ;
				}
			}
			_rep.E442(cUser.getFd(), input[2], chan->getName()); // ERR_NOTONCHANNEL
			users.clear();
			return ;
		}
	}
	_rep.E403(cUser.getFd(), cUser.getNick(), input[1]); // ERR_NOSUCHCHANNEL
}
