/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:14:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/13 11:34:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::partCmd(std::vector<std::string> &input, User &cUser)
{
	    std::vector<std::string>::iterator it = input.begin();
        std::vector<std::string>    listChannel;
        std::string                 tmp;

		if (input[0] == "PART" && input.size() < 2)
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
			for (itChannel = _channels.begin(); itChannel != _channels.end(); itChannel++)
				if (itChannel->getName() == *itListChannel)
					break ;
			if (input[0] == "PART" && itChannel == _channels.end())
			{
				_rep.E403(cUser.getFd(), cUser.getNick(), *itListChannel); // ERR_NOSUCHCHANNEL
				continue ;
			}
			if (input[0] == "PART" && !itChannel->isUser(cUser))
			{
				_rep.E442(cUser.getFd(), cUser.getNick(), *itListChannel); // ERR_NOTONCHANNEL
				continue ;
			}
			std::vector<User> chanUsers = itChannel->getUsers();
			std::string userNick;
			if (cUser.isChanOp(*itChannel))
				userNick = "@";
			userNick.append(cUser.getNick());
			for (std::vector<User>::iterator itChanUser = chanUsers.begin(); itChanUser != chanUsers.end(); itChanUser++)
			{
				if (cUser.getFd() != itChanUser->getFd())
					emit(":" + userNick + " PART " + itChannel->getName(),itChanUser->getFd());
			}
			if (itChannel->getUsrCon() - 1 == 0 && input[0] != "QUIT") {
				_channels.erase(itChannel);
			}
			else
			{
				if (itChannel->isOpUser(cUser))
				{
					itChannel->removeOpUser(cUser);
					cUser.removeOpChannel(*itChannel);
				}
				itChannel->removeUser(cUser);
				itChannel->decrUsrCon();
			}
			cUser.decrChanConnected();
		}
}
