/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:48:09 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/03 10:29:26 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * /INVITE <nickename> <channelName> : invite a user in a channel with invitation mode (mode +i)
 * @param input
 * @param cUser
 */
void Server::inviteCmd(std::vector<std::string> &input, User &cUser)
{
	if (input[1].empty() || input[2].empty())
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]); // ERR_NEEDMOREPARAMS
		return;
	}
	for (std::vector<Channel>::iterator chan = _channels.begin(); chan != _channels.end(); chan++)
	{
		std::cout << "CHANNEL NAME TO CHECK --- " << chan->getName() << " " << input[0] << " " << input[1] << std::endl;
		if (chan->getName() == input[2])
		{
			std::cout << "IN IF channel exists-----\n";
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

			// Is nickname registered in server ?
			for (std::vector<User>::iterator user = _clients.begin(); user < _clients.end(); user++)
			{
				if (user->getNick() == input[1])
				{
					// Is nickname already on channel ?
					if (chan->isUser(*user))
					{
						_rep.E443(cUser.getFd(), cUser.getNick(), chan->getName(), user->getNick()); // ERR_USERONCHANNEL
						return ;
					}
					user->addInviteChan(*chan);
					std::vector<std::string> output;
					output.push_back("PRIVMSG");
					output.push_back(user->getNick());
					output.push_back("has invited you to " + chan->getName());
					msgCmd(output, cUser);
					_rep.R341(cUser.getFd(), cUser.getNick(), user->getNick(), chan->getName()); // RPL_INVITING
					return ;
				}
			}
			std::cout << "ICI1 -----\n";
			_rep.E401(cUser.getFd(), cUser.getNick(), input[1]); // ERR_NOSUCHNICK
			std::cout << "ICI2 -----\n";
			return ;
		}
	}
	std::cout << "LALALALALA -----\n";
	_rep.E403(cUser.getFd(), cUser.getNick(), input[2]); // ERR_NOSUCHCHANNEL
}

/*
    RPL_INVITING (341)
    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_NOTONCHANNEL (442)
    ERR_CHANOPRIVSNEEDED (482)
    ERR_USERONCHANNEL (443)
*/
