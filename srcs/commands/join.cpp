/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/17 18:07:30 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO finish file

void	Server::joinCmd(std::vector<std::string> &input, int fd, User &cUser)
{
	std::vector<std::string>::iterator it = input.begin();
    it++;
    if (it >= input.end())
    {
        _rep.E461(cUser.getFd(), cUser.getNick(), "JOIN");
        return;
    }
    std::vector<Channel>::iterator itChannel = _channels.begin();
    std::string str = *it;
    std::string tmp;
    std::vector<std::string> listChan;
    std::vector<std::string> listKey;
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == ',') {
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
            if (c == ',') {
                listKey.push_back(tmp);
                tmp.clear();
            }
            else
                tmp.push_back(c);
        }
    listKey.push_back(tmp);
    tmp.clear();  
    }
    std::vector<std::string>::iterator itKey = listKey.begin();     
    for (std::vector<std::string>::iterator itLst = listChan.begin(); itLst < listChan.end(); itLst++) {
        for(std::vector<Channel>::iterator itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
            if (itChannel->getName() == *itLst)
                break;
        }
        if (itChannel == _channels.end()) { //channel n'existe pas
            if (cUser.getChanConnected() > MAX_CHAN)
            {
                _rep.E405(cUser.getFd(), cUser.getNick(),*itLst);
                return;
            }
            _channels.push_back(Channel(*itLst, cUser));
            if (listKey.size() != 0 && itKey != listKey.end()) {
                itChannel->setMode('k', true);
                itChannel->setPw(*itKey);
                itKey++;
            }
        }
        else { //channel existe
            if (itChannel->isMode('i') == true) {
                if (cUser.isMode('i') == false) {
                    _rep.E473(cUser.getFd(), cUser.getNick(), *itLst);
                    return;
                }
            }
            if (itChannel->isMode('l') == true && itChannel->getUsrCon() + 1 > itChannel->getUsrNbMax()) {
                _rep.E471(cUser.getFd(), cUser.getNick(), *itLst);
                return;
            }
            else if (itChannel->isBanned(cUser) == true) {
                _rep.E474(cUser.getFd(), cUser.getNick(), *itLst);
                return;
            }
            if (cUser.getChanConnected() > MAX_CHAN)
            {
                _rep.E405(cUser.getFd(), cUser.getNick(),*itLst);
                return;
            }
            else if (itChannel->isMode('k') == true) {
                if (listKey.size() != 0 && itKey != listKey.end()) {
                    if (*itKey != itChannel->getPw()) {
                        _rep.E475(cUser.getFd(), cUser.getNick(), itChannel->getName());
                        return;
                    }
                }
                else {
                    _rep.E475(cUser.getFd(), cUser.getNick(), itChannel->getName());
                    return;
                }
            }
            itChannel->addUser(cUser);
            itChannel->incrUsrCon();
            if (itChannel->getIsTopic() == true)
                _rep.R332(cUser.getFd(), cUser.getNick(), itChannel->getName(), itChannel->getSubject());
            for (std::vector<User>::iterator itU = _clients.begin(); itU < _clients.end(); itU++) {
                _rep.R353(cUser.getFd(), cUser.getNick(), itChannel->getName(), itU->getNick(),itChannel->getChanPrefix(), itChannel->getUserPrefix());
            }
            _rep.R366(cUser.getFd(), cUser.getNick(), itChannel->getName());
            _io.emit(":" + cUser.getNick() + " JOIN " + itChannel->getName(),cUser.getFd());
        }
    }
}
