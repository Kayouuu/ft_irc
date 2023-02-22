/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/22 15:40:42 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO finish file

void	Server::joinCmd(std::vector<std::string> &input, int fd, User &cUser)
{
    std::cout << "entre cmd JOIN\n";
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
    str.clear();
    std::vector<std::string>::iterator itKey = listKey.begin();
    std::cout << "fin parsing\n";
    for (std::vector<std::string>::iterator itLst = listChan.begin(); itLst < listChan.end(); itLst++) {
        str = *itLst;
        if(str[0] != '#')
            return;
        str.clear();
        for(std::vector<Channel>::iterator itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
            if (itChannel->getName() == *itLst)
                break;
        }
        if (itChannel == _channels.end()) { //channel n'existe pas
            std::cout << "chan existe pas\n";
            if (cUser.getChanConnected() > MAX_CHAN)
            {
                _rep.E405(cUser.getFd(), cUser.getNick(),*itLst);
                return;
            }
            std::cout << *itLst << " : chan avant creation\n";
            Channel newChan = Channel(*itLst, cUser);
            std::cout << "chan cree, " << &newChan << std::endl;
			// a refaire la condition
//            if (listKey.size() != 0 && itKey != listKey.end()) {
//                newChan.setMode('k', true);
//                std::cout << "HERE\n";
//                newChan.setPw(*itKey);
//                itKey++;
//            }
            _channels.push_back(newChan);
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
                         std::cout << "une cle\n";
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
        }
    std::cout << "avant msg fin join\n";
    for(itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
    		if (itChannel->getName() == *itLst)
	    		break;
    	}
    if (itChannel == _channels.end()){
        std::cout << "probleme de type pas cree";
        return;
    }
    	std::vector<User> users = itChannel->getUsers();
	    for (std::vector<User>::iterator itU = users.begin(); itU < users.end(); itU++) {
		    _rep.R353(cUser.getFd(), cUser.getNick(), itChannel->getName(), itU->getNick(),itChannel->getChanPrefix(), itChannel->getUserPrefix());
	    }
	    _rep.R366(cUser.getFd(), cUser.getNick(), itChannel->getName());
	    _io.emit(":" + cUser.getNick() + " JOIN " + itChannel->getName(),cUser.getFd());
    }
    std::cout << "fin cmd JOIN\n";
}
