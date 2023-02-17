/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/15 17:28:22 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO test msg to channel
void Server::msgCmd(std::vector<std::string> &input, int fd, User &cUser) {
    std::cout << "---entering msgCmd---\n";
    std::vector<std::string>::iterator it = input.begin();
    std::vector<std::string>::iterator itTmp;
    std::vector<User>::iterator itClient = _clients.begin();
    std::string msg;
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
        if (it >= input.end()) {
            _rep.E412(cUser.getFd(), cUser.getNick());
            return;
        }
        for (itClient; itClient < _clients.end(); itClient++) {
            itTmp = it;
            //a voir ce que weechat ecrit avant ce message
            for (it; it < input.end(); it++) {
                msg = msg.append(*it);
                if (it < --input.end())
                    msg = msg.append(" ");
            }
            _io.emit(msg + "\r\n", itClient->getFd());
            msg.clear();
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
                if (it >= input.end()) {
                    _rep.E412(cUser.getFd(), cUser.getNick());
                    return;
                }
                itTmp = it;
                _io.emit("MSG(" + cUser.getNick() + "):", itClient->getFd());
                for (it; it < input.end(); it++) {
                    msg = msg.append(*it);
                    if (it < --input.end())
                        msg = msg.append(" ");
                }
                _io.emit(msg + "\r\n", itClient->getFd());
                msg.clear();
                it = itTmp;
            }
            else
                _rep.E401(cUser.getFd(), cUser.getNick(), *itList);
        }
    }
    std::cout << "---leaving msgCmd---\n";
}
