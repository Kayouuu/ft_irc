/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:06:27 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/15 15:56:25 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO check for channel
void Server::noticeCmd(std::vector<std::string> &input, int fd, User &cUser) {
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
            return;
        }
        else if (itChannel->isBanned(cUser) == 1) {
            return;
        }
        it++;
        if (it >= input.end()) {
            return;
        }
        for (itClient; itClient < _clients.end(); itClient++) {
            itTmp = it;
            //a voir ce que weechat ecrit avant ce message
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
        std::vector<std::string>::iterator itList = listUsers.begin();
        while (itClient != _clients.end()) {
            if (itClient->getNick() == *itList)
                break;
            itClient++;
        }
        if (itClient != _clients.end()){
            itTmp = it;
            // _io.emit("NOTICE ->(" + cUser.getNick() + "):", itClient->getFd());
            for (it; it < input.end(); it++) {
                _io.emit(*it, itClient->getFd());
                if (it < --input.end())
                    _io.emit(" ", itClient->getFd());
            }
            it = itTmp;
        }
    }
}
