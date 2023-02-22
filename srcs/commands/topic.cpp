/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:21:31 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/22 15:52:45 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::topicCmd(std::vector<std::string> &input, int fd, User &cUser)
{
	std::vector<Channel>::iterator	it;
	if (input.size() < 3)
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
		return ;
	}
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->getName() == input[1])
			break ;
	}
	if (it == _channels.end())
	{
		// TODO channel don't exist
		return ;
	}
	std::vector<User> users = it->getUsers();
	if (input.size() == 3)
	{
		// _rep.R332(cUser.getFd(), cUser.getNick(), input[0], it->); TODO getTopic() function
	}
	else
	{
		if (it->isOpUser(cUser))
		{
			// TODO set topic	
		}
		else
		{
			_rep.E482(cUser.getFd(), cUser.getNick(), input[1]);
		}
	}
}
