/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbanned.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:50:06 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/27 12:24:34 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void Server::isbanned(std::vector<std::string> &input, User &cUser)
{
    if (cUser.isIrcOp()) {
        if (input[1][0] == '#') {
            std::vector<Channel>::iterator itChan = _channels.begin();
            for (; itChan != _channels.end(); itChan++) {
                if (itChan->getName() == input[1])
                    break;
            }
            if (itChan == _channels.end())
                _rep.E403(cUser.getFd(), cUser.getNick(), input[1]);
            std::vector<User> users = itChan->getUsers();
            std::vector<User>::iterator itUsers = users.begin();
            for (; itUsers != users.end(); itUsers++) {
                if (itUsers->getNick() == input[2])
                    break;
            }
            if (itUsers == users.end())
                _rep.E401(cUser.getFd(), cUser.getNick(), input[2]);
            if (itChan->isBanned(*itUsers))
                _rep.R367(cUser.getFd(), cUser.getNick(), input[1], input[2]);//msg is ban;
            else
                ;//TODO? msg is NOT ban
        }
    }
}