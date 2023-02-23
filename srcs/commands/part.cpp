/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:14:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/23 10:20:27 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::partCmd(std::vector<std::string> &input, User &cUser)
{
	    std::vector<std::string>::iterator it = input.begin();
        std::vector<std::string>    listChannel;
        std::string                 tmp;

		if (input.size() < 2)
		{
			_rep.E461(cUser.getFd(), cUser.getNick(), input[0]); // ERRO_NEEDMOREPARAMS
			return ;
		}
		it++;
        std::string                 str = *it;
		it++;
		
        for (size_t i = 0; i < str.length(); i++) {
            char c = str[i];
            if (c == ',') {
                listChannel.push_back(tmp);
                tmp.clear();
            }
            else if (!std::isspace(c))
                tmp.push_back(c);
        }
        listChannel.push_back(tmp);
		
		for (std::vector<std::string>::iterator itListChannel = listChannel.begin(); itListChannel != listChannel.end(); itListChannel++)
		{
			std::vector<Channel>::iterator itChannel;
			for (itChannel = _channels.begin(); itChannel != _channels.end(); it++)
				if (itChannel->getName() == *itListChannel)
					break ;
			if (itChannel == _channels.end())
			{
				_rep.E403(cUser.getFd(), cUser.getNick(), *itListChannel); // ERR_NOSUCHCHANNEL
				continue ; // TOCHECK maybe return ? Either we continue browsing the list of channels or we stop when a channel don't exist
			}
			if (!itChannel->isUser(cUser))
			{
				_rep.E442(cUser.getFd(), cUser.getNick(), *itListChannel); // ERR_NOTONCHANNEL
				continue ; // TOCHECK maybe return ? Either we continue browsing the list of channels or we stop when a channel don't exist
			}
			itChannel->removeOpUser(cUser);
			itChannel->removeUser(cUser);
			itChannel->decrUsrCon();
		}
}
