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
				throw std::exception();//error msg: channel <input[1]> is not in invite mode (+i)
			//user is op ?
			if (!it->isOpUser(cUser))
				throw std::exception();//error msg: user <cUser> is not a channel operator
			//nickname is registered in server ?

		}
	}
	throw std::exception();//error msg: no channel named <input[1]>
}
