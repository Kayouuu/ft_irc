/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:03 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/03 11:54:41 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::quitCmd(std::vector<std::string> &input, User &cUser)
{
	std::vector<Channel>::iterator itChan = _channels.begin();
    for (; itChan != _channels.end(); itChan++) {
		if (_channels.size() == 0)
			break ;
		std::vector<User> chanUsers = itChan->getUsers();
		for (std::vector<User>::iterator itChanUser = chanUsers.begin(); itChanUser != chanUsers.end(); itChanUser++)
		{
			if (itChanUser->getNick() != cUser.getNick())
				_io.emit(":" + cUser.getNick() + " PART " + itChan->getName(),itChanUser->getFd());
		}
		if(itChan->getUsrCon() - 1 == 0)
			_channels.erase(itChan);
		else {
			if (!itChan->isUser(cUser))
				continue;
			if (itChan->isOpUser(cUser))
				itChan->removeOpUser(cUser);
			itChan->removeUser(cUser);
			itChan->decrUsrCon();
		}
    }
    std::vector<User>::iterator itUser = _clients.begin();
    for (; itUser != _clients.end(); itUser++)
    {
        if (itUser->getNick() == cUser.getNick())
        {
			close(cUser.getFd());
            _clients.erase(itUser);
            User	tmp_user = User();
		    _clients.push_back(tmp_user);
            break ;
        }
    }
	_connected_clients--;
}
