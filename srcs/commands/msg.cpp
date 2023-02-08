/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/02/08 19:33:12 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void Server::msgCmd(std::vector<std::string> input, int fd, User &cUser) {
    std::vector<std::string>::iterator it = input.begin() + 1;
    if (it[0] == "#") {
        std::vector<Channel>::iterator itChannel = _channels.begin();
        while (itChannel != _channels.end()) {
            if (*itChannel == *it)
                break;
            itChannel++;
        }
        if (itChannel == _channels.end()) {
            _rep.E404(cUser.getFd(),cUser.getNick(), *itChannel);
            return;
        }
        else if (itChannel.isBanned(cUser) == 1) {
            return;
        }
        it++;
        std::for_each(_clients.begin(), _clients.end(), _io.emit(*it, _clients.getFd()));
    }
    else {
        std::vector<User>::iterator itClient = _clients.begin();
        if (*it.find(",") != std::string::npos) {
            //occurence trouver!
        }
        while (itClient != _clients.end()) {
            if (*itClient == *it)
                break;
            itClient++;
        }
    }
}
