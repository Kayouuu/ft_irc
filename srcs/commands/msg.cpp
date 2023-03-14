/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:56:08 by lbattest          #+#    #+#             */
/*   Updated: 2023/03/13 11:34:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * Send a message to a #channel or a user
 * Paramètres: <destinataire>{,<destinataire>} <texte à envoyer>
 * @param input[1] #channel,... OR user,...
 * @param input[2,...] msg
 * @param cUser
 */
void Server::msgCmd(std::vector<std::string> &input, User &cUser) {
    std::string msg;
    std::vector<std::string>::iterator it = input.begin();
    std::vector<std::string>::iterator itTmp;
    if (input.size() < 3)
    {
        _rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
        return ;
    }
    it++;
    msg = *it;
	if (msg[0] == '#') { /* msg to a channel */
		msg.clear();
		std::vector<Channel>::iterator itChannel = _channels.begin();
		for (;itChannel != _channels.end(); itChannel++) {
			if (itChannel->getName() == *it) {
				break;
			}
		}
		if (itChannel == _channels.end()) {
			_rep.E404(cUser.getFd(), cUser.getNick(), *it);
			return;
		}
		if (itChannel->isBanned(cUser) == 1) {
			return;
		}
		if (itChannel->isMode('n')) /* can't msg the channel if you're not in it */
		{
			if (!itChannel->isUser(cUser)) {
				return;
			}
		}
		if (itChannel->isMode('m'))
		{
			if (!cUser.isVoicedChan(*itChannel) && !cUser.isChanOp(*itChannel) && !cUser.isIrcOp()) {
				return;
			}
		}
		it++;
		if (it >= input.end()) {
			_rep.E412(cUser.getFd(), cUser.getNick());
			return;
		}
		std::vector<User> vUser = itChannel->getUsers();
		std::vector<User>::iterator itClient = vUser.begin();
		for (; itClient < vUser.end(); itClient++) {
            if (itClient->getFd() != -1) {
                if (itClient->getFd() == cUser.getFd())
                    continue;
                itTmp = it;
				std::string prefix;
				if (itChannel->getUserPrefix(cUser) != 'u')
					prefix.append(1, itChannel->getUserPrefix(cUser));
                msg.append(":" + prefix + cUser.getNick() + " " + input[0] + " " + itChannel->getName() + " ");
                for (; it < input.end(); it++) {
                    msg.append(*it);
                    if (it < --input.end())
                        msg.append(" ");
                }
				if (!itChannel->isBanned(*itClient))
                	emit(msg, itClient->getFd());
                msg.clear();
                it = itTmp;
            }
        }
    }
    else { /* msg to a user */
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
		std::vector<User>::iterator itClient = _clients.begin();
        for (std::vector<std::string>::iterator itList = listUsers.begin(); itList < listUsers.end(); itList++) {
            while (itClient != _clients.end()) {
                if (itClient->getNick() == *itList)
                    break;
                itClient++;
            }
            if (itClient != _clients.end()) {
                if (it >= input.end()) {
                    _rep.E412(cUser.getFd(), cUser.getNick());
                    return;
                }
                itTmp = it;
                msg.append(":" + cUser.getNick() + " " + input[0] + " " + itClient->getNick() + " ");
                for (; it < input.end(); it++) {
                    msg.append(*it);
                    if (it < --input.end())
                        msg.append(" ");
                }
				emit(msg, itClient->getFd());
				if (!cUser.isInitConv() && input[0] != "NOTICE")
				{
					emit(msg, cUser.getFd());
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
