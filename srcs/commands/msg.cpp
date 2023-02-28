/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/27 12:00:35 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void Server::msgCmd(std::vector<std::string> &input, User &cUser) {

    if (input[1] == "TheMysteryMachine")
    {
        _bot.setMsg(input, cUser);
        return ;
    }
    std::string msg;
    std::vector<std::string>::iterator it = input.begin();
    std::vector<std::string>::iterator itTmp;
    std::vector<User>::iterator itClient = _clients.begin();
    it++;
    msg = *it;
    if (msg[0] == '#') {
        itClient++;
        msg.clear();
        std::vector<Channel>::iterator itChannel = _channels.begin();
        while (itChannel != _channels.end()) {
            if (itChannel->getName() == *it)
                break;
            itChannel++;
        }
        if (itChannel == _channels.end()) {
            _rep.E404(cUser.getFd(), cUser.getNick(), itChannel->getName());
            return;
        }
        else if (itChannel->isBanned(cUser) == 1) {
            return;
        }
        if (itChannel->isMode('n')) {
			if (!itChannel->isUser(cUser))
				return;
		}
		if (itChannel->isMode('m')) {
			if (!cUser.isVoicedChan(*itChannel))
				return;
		}
        it++;
        if (it >= input.end()) {
            _rep.E412(cUser.getFd(), cUser.getNick());
            return;
        }
        for (itClient; itClient < _clients.end(); itClient++) {
            if (itClient->getFd() != -1) {
                if (*itClient == cUser)
                    continue;
                itTmp = it;
                msg.append(":" + cUser.getNick() + " PRIVMSG " + itChannel->getName() + " ");
                for (it; it < input.end(); it++) {
                    msg.append(*it);
                    if (it < --input.end())
                        msg.append(" ");
                }
                _io.emit(msg, itClient->getFd());
                msg.clear();
                it = itTmp;
            }
        }
    }
    else {
        msg.clear();
        std::vector<std::string>    listUsers;
        std::string                 tmp;
        std::string                 str = *it;
        it++;
        for (size_t i = 0; i < str.length(); i++) {
            char c = str[i];
            if (c == ',') {
                listUsers.push_back(tmp);
                tmp.clear();
            }
            else if (!std::isspace(c))
                tmp.push_back(c);
        }
        listUsers.push_back(tmp);
        for (std::vector<std::string>::iterator itList = listUsers.begin(); itList < listUsers.end(); itList++) {
            while (itClient != _clients.end()) {
                if (itClient->getNick() == *itList)
                    break;
                itClient++;
            }
            if (itClient != _clients.end()){
                if (it >= input.end()) {
                    _rep.E412(cUser.getFd(), cUser.getNick());
                    return;
                }
                itTmp = it;
                msg.append(":" + cUser.getNick() + " PRIVMSG " + itClient->getNick() + " ");
                for (it; it < input.end(); it++) {
                    msg.append(*it);
                    if (it < --input.end())
                        msg.append(" ");
                }
				_io.emit(msg, itClient->getFd());
				if (!cUser.isInitConv())
				{
					_io.emit(msg, cUser.getFd());
					cUser.setInitConv(true);
					itClient->setInitConv(true);
				}
                msg.clear();
                it = itTmp;
            }
            else
                _rep.E401(cUser.getFd(), cUser.getNick(), *itList);
        }
    }
}
