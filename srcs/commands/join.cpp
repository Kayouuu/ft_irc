/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/17 11:14:09 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO finish file
void	Server::joinCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
	std::vector<std::string>::iterator it = input.begin();
    it++;
    if (cUser.getChanConnected() > MAX_CHAN)
    {
        _rep.E405(cUser.getFd(), *it);
        return;
    }
    if (it >= input.end())
    {
        _rep.E461(cUser.getFd(), cUser.getNick(), "JOIN");
        return;
    }
    std::vector<Channel>::iterator itChannel = _channels.begin();
    while (itChannel != _channels.end())
    {
        if (itChannel->getName() == *it)
            break;
        itChannel++;
    }
    if (itChannel == _channels.end())
    {
        _rep.E403(cUser.getFd(), cUser.getNick(), *it);
        return;
    }
    if (itChannel->isMode('i') == 1) {
        _rep.E473(cUser.getFd(), cUser.getNick(), *it);
        return;
    }
    if (it == input.end()) {
        _rep.E461(cUser.getFd(), cUser.getNick(), "JOIN");
        return;
    }
    std::string str = *it;
    std::string tmp;
    std::vector<std::string> listChan;
    std::vector<std::string> listKey = NULL;
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == ",") {
            listChan.push_back(tmp);
            tmp.clear();
        }
        else
            tmp.push_back(c);
    }
    listChan.push_back(tmp);
    tmp.clear();
    it++;
    if (it != input.end()) {
        for (size_t i = 0; i < str.length(); i++) {
            char c = str[i];
            if (c == ",") {
                listKey.push_back(tmp);
                tmp.clear();
            }
            else
                tmp.push_back(c);
        }
    listKey.push_back(tmp);
    tmp.clear();  
    std::vector<std::string>::iterator itKey = listKey.begin();     
    }
    for (std::vector<std::string>::iterator itLst = listChan.begin(); itLst < listChan.end(); itLst++) {
        for(std::vector<Channel>::iterator itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
            if (itChannel.getName() == *it)
                break;
        }
        if (itChannel == _channels.end()) { //channel n'existe pas
            //check si toomanychannel n'est pas atteins
            _channels.push_back(channel(*it, cUser));
            if (listKey != NULL && itKey != listKey.end()) {
                itChannel->setMode('k', true);
                setPw(*itKey);
                itKey++;
            }
            //voir si besoin de setup un topic tout decuite ou envoyer RPL_NOTOPIC
        }
        else { //channel existe
            if (isMode('l') == true && itChannel->getUsrConnected() + 1 > itChannel->getUsrNbMax()) {
                _rep.E471(cUser.getFd(), cUser.getNick(), *it);
                return;
            }
            else if (itChannel->isBanned(cUser) == true) {
                _rep.E474(cUser.getFd(), cUser.getNick(), *it);
                return;
            }
            //check si toomanychannel n'est pas atteins
            else if (itChannel->isMode('k') == true) {
                if (listKey != NULL && itKey != listKey.end()) {
                    if (*listKey != itChannel->getPw()) {
                        _rep.E475(cUser.getFd(), cUser.getNick(), *itChannel);
                        return;
                    }
                }
                else {
                    _rep.E475(cUser.getFd(), cUser.getNick(), *itChannel);
                    return;
                }
            }
            itChannel->addUser(cUser);
            //envoyer RPL_TOPIC ?
        }
    }
}
