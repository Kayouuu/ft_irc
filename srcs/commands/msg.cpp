/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/13 14:50:21 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO test msg to channel
void Server::msgCmd(std::vector<std::string> &input, int fd, User &cUser) {
    std::cout << "---entering msgCmd---\n";
    std::vector<std::string>::iterator it = input.begin();
    std::vector<User>::iterator itClient = _clients.begin();
    it++;
    if (it[0] == "#") {
        std::cout << "msg to channel\n";
        std::vector<Channel>::iterator itChannel = _channels.begin();
        while (itChannel != _channels.end()) {
            if (itChannel->getName() == *it)
                break;
            itChannel++;
        }
        if (itChannel == _channels.end()) {
            _rep.E404(cUser.getFd(),cUser.getNick(), itChannel->getName());
            return;
        }
        else if (itChannel->isBanned(cUser) == 1) {
            return;
        }
        it++;
        for (itClient; itClient < _clients.end(); itClient++) {
            _io.emit(*it, itClient->getFd());
        }
    }
    else {
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
            if (itClient != _clients.end())
                _io.emit(*it, itClient->getFd());
            else
                _rep.E401(cUser.getFd(), cUser.getNick(), *itList);
        }
    }
    std::cout << "---leaving msgCmd---\n";
}
