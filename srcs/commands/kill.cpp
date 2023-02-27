/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:35:47 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/27 15:04:01 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void 	Server::killCmd(std::vector<std::string> &input, User &cUser)
{
    if (!cUser.isIrcOp()) {
        _rep.E481(cUser.getFd(), cUser.getNick());
        return;
    }
    std::vector<std::string>::iterator it = input.begin();
    it++;
    if (it == input.end()) {
        _rep.E461(cUser.getFd(), cUser.getNick(), "KILL");
    }
    std::vector<User>::iterator itClients;
    for (; itClients != _clients.end(); itClients++) {
        if (itClients->getNick() == input[1])
            break;
    }
    if (itClients == _clients.end()){
        _rep.E401(cUser.getFd(), cUser.getNick(), input[1]);
        return;
    }
    std::vector<Channel>::iterator itChan = _channels.begin();
    for (; itChan != _channels.end(); itChan++) {
        if (!itChan->isUser(*itClients))
            continue;
        if (itChan->isOpUser(*itClients))
            itChan->removeOpUser(*itClients);
        itChan->removeUser(*itClients);
        itChan->decrUsrCon();
    }
    itClients->resetUser();
	_connected_clients--;
}
