/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/24 10:19:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO finish file

void    Server::usrJoinChan(User &cUser, Channel &chan)
{
    std::vector<std::string> input;

	chan.addUser(cUser);
	chan.incrUsrCon();
    input.push_back("NOTICE");
    input.push_back(chan.getName());
    input.push_back("has joined " + chan.getName());
    noticeCmd(input, cUser);
}

void	Server::joinCmd(std::vector<std::string> &input, User &cUser)
{
    // std::cout << "entre cmd JOIN\n";
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
    bool isPw = false;
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
        str.clear();
        str = *it;
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
        isPw = true;
    }
    str.clear();
    std::vector<std::string>::iterator itKey = listKey.begin();
    // std::cout << "fin parsing\n";
    for (std::vector<std::string>::iterator itLst = listChan.begin(); itLst < listChan.end(); itLst++) {
        str = *itLst;
        if(str[0] != '#'){
			str.clear();
			continue;
		}
        str.clear();
        for(; itChannel < _channels.end(); itChannel++) {
			// std::cout << *itLst << ", " << itChannel->getName() << std::endl;
			if (itChannel->getName() == *itLst) {
				break;
			}
        }
        if (itChannel == _channels.end()) { //channel n'existe pas
            // std::cout << "chan existe pas\n";
            if (cUser.getChanConnected() > MAX_CHAN)
            {
                _rep.E405(cUser.getFd(), cUser.getNick(),*itLst);
                return;
            }
            Channel newChan = Channel(*itLst, cUser);
            if (isPw == true && itKey != listKey.end()) {
               newChan.setMode('k', true);
               newChan.setPw(*itKey);
               itKey++;
           }
			_channels.push_back(newChan);
			for(itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
				if (itChannel->getName() == *itLst) {
					break;
				}
			}
			if (itChannel == _channels.end()){
				// std::cout << "probleme de type pas cree";
				return;
			}
			std::vector<User> users = itChannel->getUsers();
			for (std::vector<User>::iterator itU = users.begin(); itU != users.end(); itU++) {
				if (cUser.getFd() != -1) {
					// std::cout << cUser.getFd(), cUser.getNick() << ", " << cUser.getNick()<< ", " << itChannel->getName()<< ", " << itU->getNick()<< ", " <<itChannel->getChanPrefix()<< ", " << itChannel->getUserPrefix(*itU, *itChannel) <<std::endl;
					_rep.R353(cUser.getFd(), cUser.getNick(), itChannel->getName(), itU->getNick(),itChannel->getChanPrefix(), itChannel->getUserPrefix(*itU, *itChannel));
				}
			}
			_rep.R366(cUser.getFd(), cUser.getNick(), itChannel->getName());
			_io.emit(":" + cUser.getNick() + " JOIN " + itChannel->getName(),cUser.getFd());
            users.clear();
		}
        else if (!itChannel->isUser(cUser)) { //channel existe
			// std::cout << "chan existe\n";
            if (itChannel->isMode('i')) {
				std::cout << "chan mode i\n";
                if (!cUser.isInviteChan(*itChannel)) {
                    _rep.E473(cUser.getFd(), cUser.getNick(), *itLst);
                    return;
                }
				cUser.removeInviteChan(*itChannel);
            }
			std::cout << itChannel->getUsrCon() << " nb personne co avant toi bg\n";
			// condition a change apres la pause
            if (itChannel->isMode('l')) {
				std::cout << "chan mode +l avec en max " << itChannel->getUsrNbMax() << std::endl;
				if (itChannel->getUsrCon() + 1 > itChannel->getUsrNbMax()) {
					_rep.E471(cUser.getFd(), cUser.getNick(), *itLst);
					return;
				}
			}
            else if (itChannel->isBanned(cUser)) {
                _rep.E474(cUser.getFd(), cUser.getNick(), *itLst);
                return;
            }
            if (cUser.getChanConnected() > MAX_CHAN)
            {
                _rep.E405(cUser.getFd(), cUser.getNick(),*itLst);
                   return;
            }
            else if (itChannel->isMode('k')) {
                if (isPw && itKey != listKey.end()) {
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
            if (itChannel->getIsTopic())
                _rep.R332(cUser.getFd(), cUser.getNick(), itChannel->getName(), itChannel->getSubject());
			for(itChannel = _channels.begin(); itChannel < _channels.end(); itChannel++) {
				if (itChannel->getName() == *itLst)
					break;
			}
			if (itChannel == _channels.end()){
				// std::cout << "probleme de type pas cree";
				return;
			}
			usrJoinChan(cUser, *itChannel);
			std::cout << itChannel->getUsrCon() << " nb personne co apres toi bg\n";
			std::vector<User> users = itChannel->getUsers();
			for (std::vector<User>::iterator itU = users.begin(); itU < users.end(); itU++) {
				_rep.R353(cUser.getFd(), cUser.getNick(), itChannel->getName(), itU->getNick(),itChannel->getChanPrefix(), itChannel->getUserPrefix(*itU, *itChannel));
			}
			_rep.R366(cUser.getFd(), cUser.getNick(), itChannel->getName());
			_io.emit(":" + cUser.getNick() + " JOIN " + itChannel->getName(),cUser.getFd());
            users.clear();
		}
    }
    // std::cout << "fin cmd JOIN\n";
}
