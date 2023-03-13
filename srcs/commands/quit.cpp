/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:03 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/13 10:00:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::quitCmd(std::vector<std::string> &input, User &cUser)
{
	std::vector<Channel> chanDel;
	if (cUser.getChanConnected() != 0)
	{
		std::vector<Channel>::iterator itChan = _channels.begin();
		for (; itChan != _channels.end(); itChan++) {
			std::vector<std::string> output;
			output.push_back("QUIT");
			output.push_back(itChan->getName());
			output.push_back(cUser.getNick());
			partCmd(output, cUser);
			if (itChan->getUsrCon() - 1 == 0)
				chanDel.push_back(*itChan);
		}
	}
	chanDel.clear();
    std::vector<User>::iterator itUser = _clients.begin();
    for (; itUser != _clients.end(); itUser++)
    {
        if (itUser->getFd() == cUser.getFd())
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
