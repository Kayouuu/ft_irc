/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/15 12:01:26 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO test msg to channel
void Server::msgCmd(std::vector<std::string> &input, int fd, User &cUser) {
    std::cout << "---entering msgCmd---\n";
    std::vector<std::string>::iterator it = input.begin();
    std::vector<std::string>::iterator itTmp;
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
            itTmp = it;
            for (it; it < input.end(); it++) {
                _io.emit(*it, itClient->getFd());
                if (it < --input.end())
                    _io.emit(" ", itClient->getFd());
            }
            it = itTmp;
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
            if (itClient != _clients.end()){
                itTmp = it;
                _io.emit("MSG(" + cUser.getNick() + "):", itClient->getFd());
                for (it; it < input.end(); it++) {
                    _io.emit(*it, itClient->getFd());
                    if (it < --input.end())
                        _io.emit(" ", itClient->getFd());
                }
                it = itTmp;
            }
            else
                _rep.E401(cUser.getFd(), cUser.getNick(), *itList);
        }
    }
    std::cout << "---leaving msgCmd---\n";
}
