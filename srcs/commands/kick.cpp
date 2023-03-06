/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:33:55 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/03 10:26:25 by psaulnie         ###   ########.fr       */
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
	if (input[1].empty() || input[2].empty())
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
					chan->removeUser(*user);
					if (!input[3].empty())
						_io.emit(": " + cUser.getNick() + " " + input[0] + " " + user->getNick() + " " + input[3], cUser.getFd()); // send message if it exists
					else
						_io.emit(": " + cUser.getNick() + " " + input[0] + " " + user->getNick(), cUser.getFd()); // TODO not sure if I have to send this
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

//_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);			// ERR_NEEDMOREPARAMS		[OK]
//_rep.E403(cUser.getFd(), cUser.getNick(), input[1]);			// ERR_NOSUCHCHANNEL		[OK]
//_rep.E476(fd, chan->getName());					// ERR_BADCHANMASK			[MISSING]
//_rep.E482(cUser.getFd(), cUser.getNick(), chan->getName());	// ERR_CHANOPRIVSNEEDED		[OK]
//_rep.E442(cUser.getFd(), cUser.getNick(), chan->getName());	// ERR_NOTONCHANNEL			[OK]
//_rep.E442(fd, input[2], chan->getName());			// ERR_NOTONCHANNEL			[OK]

// The KICK command is used to forcibly remove a user from a channel (force PART).
// Only a channel operator can kick another user from a channel.

//QUESTION: Does it send a response to the client ? Apparently not
//QUESTION: do we have to create a blacklist of people who cannot longer join the channel from wich they've been kicked ? NO
//QUESTION: is the kicked client notified he's been kicked ?
//QUESTION: is a message sent in the channel to notify the other users in the channel than someone's been kicked ?
//QUESTION: can the opchannel user kick hiself ?
