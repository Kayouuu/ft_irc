/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:41:26 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/01 10:41:26 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

/**
 * Set chan operator status to a user/users
 * @param input[1] #channel
 * @param input[2] user1,user2,...
 * @param cUser
 */
//void Server::opCmd(std::vector<std::string> &input, User &cUser) {
//	std::vector<Channel>::iterator itChan = _channels.begin();
//	for (; itChan != _channels.end(); itChan++) {
//		if (itChan->getName() == input[1])
//			break;
//	}
//	if (itChan == _channels.end()) {
//		_rep.E403(cUser.getFd(), cUser.getNick(), input[1]);
//		return;
//	}
//	if (!itChan->isOpUser(cUser)) {
//		_rep.E482(cUser.getFd(), cUser.getNick(), input[1]);
//		return;
//	}
//	std::string str = input[2];
//	std::string tmp;
//	std::vector<std::string> newOp;
//	for (size_t i = 0; i != str.length(); i++) {
//		char c = str[1];
//		if (c == ',') {
//			newOp.push_back(tmp);
//			tmp.clear();
//		}
//		else
//			tmp.push_back(c);
//	}
//	newOp.push_back(tmp);
//	std::vector<User>::iterator itUsers = _clients.begin();
//	std::vector<std::string>::iterator itNewOp = newOp.begin();
//	for (; itNewOp != newOp.end(); itNewOp++) {
//		for (; itUsers != _clients.end(); itUsers++) {
//			if (itUsers->getNick() == *itNewOp)
//				break;
//		}
//		if (itUsers == _clients.end()) {
//			_rep.E401(cUser.getFd(), cUser.getNick(), *itNewOp);
//			continue;
//		}
//		if (!itChan->isUser(*itUsers))
//			continue;
//		itChan->addOpUser(*itUsers);
//		itUsers->addOpChannel(*itChan);
//	}
//}

/**
 * Set chan operator status to a user/users
 * @param input[1] user1
 * @param input[2] user2
 * @param input[n] usern
 * @param cUser
 */
void Server::opCmd(std::vector<std::string> &input, User &cUser)
{
	std::cout << cUser.getNick() << " set " << input[1] << " as chanop\n";
}
