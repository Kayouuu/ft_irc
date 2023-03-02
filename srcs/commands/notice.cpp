/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:06:27 by lbattest          #+#    #+#             */
/*   Updated: 2023/03/02 15:05:30 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void Server::noticeCmd(std::vector<std::string> &input, User &cUser) {
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
            return;
        }
        else if (itChannel->isBanned(cUser) == 1) {
            return;
        }
        if (itChannel->isMode('n') == true)
            return;
        it++;
        if (it >= input.end()) {
            return;
        }
        for (itClient; itClient < _clients.end(); itClient++) {
            if (itClient->getFd() != -1) {
                if (*itClient == cUser)
                    continue;
                itTmp = it;
                msg.append(":" + cUser.getNick() + " NOTICE " + itChannel->getName() + " ");
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
                    return;
                }
                itTmp = it;
                msg.append(":" + cUser.getNick() + " NOTICE " + itClient->getNick() + " ");
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
}
