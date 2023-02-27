/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:03 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/27 15:03:12 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::quitCmd(std::vector<std::string> &input, User &cUser)
{
	std::vector<Channel>::iterator itChan = _channels.begin();
    for (; itChan != _channels.end(); itChan++) {
        if (!itChan->isUser(cUser))
            continue;
        if (itChan->isOpUser(cUser))
            itChan->removeOpUser(cUser);
        itChan->removeUser(cUser);
        itChan->decrUsrCon();
    }
	cUser.resetUser();
	_connected_clients--;
}

//QUESTION: do we have to remove user from channels he's in ?
