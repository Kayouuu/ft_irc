/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:21:31 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/23 10:03:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::topicCmd(std::vector<std::string> &input, User &cUser)
{
	std::vector<Channel>::iterator	itChannel;
	std::vector<User> users;

	if (input.size() < 2)
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
		return ;
	}
	for (itChannel = _channels.begin(); itChannel != _channels.end(); itChannel++)
		if (itChannel->getName() == input[1])
			break ;
	if (itChannel == _channels.end())
	{
		_rep.E403(cUser.getFd(), cUser.getNick(), input[1]);
		return ;
	}
	users = itChannel->getUsers();
	if (input.size() == 2)
	{
		if (itChannel->getIsTopic())
			_rep.R332(cUser.getFd(), cUser.getNick(), input[1], itChannel->getSubject());
		else
			_rep.R331(cUser.getFd(), cUser.getNick(), input[1]);
	}
	else
	{
		if (itChannel->isOpUser(cUser))
		{
			std::string							subject;
			std::vector<std::string>::iterator	itSubject = input.begin();

			itSubject++;
			itSubject++;
			for (itSubject; itSubject != input.end(); itSubject++)
			{
				if (*itSubject != "")
					subject.append(*itSubject);
			}
			if (subject[0] == ':')
				subject.erase(subject.begin());
			itChannel->setSubject(subject);
			itChannel->setIsTopic(true);
		}
		else
			_rep.E482(cUser.getFd(), cUser.getNick(), input[1]);
	}
	users.clear();
}
