/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:10:55 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/01 14:09:45 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
//TODO if user change his nickname in channel, change new username in database Channel ET Server

void	Server::nickCmd(std::vector<std::string> &input, User &cUser)
{
	if (input[1] == "")
	{
		_rep.E431(cUser.getFd(), cUser.getNick());
		return ;
	}
	if (input[1].size() > 9 || input[1][0] == '#') // TODO check unwanted character
	{
		_rep.E432(cUser.getFd(), cUser.getNick(), input[1]);
		return ;
	}
	for (std::vector<User>::iterator it = _clients.begin(); it < _clients.end(); it++)
	{
		if (it->getNick() == input[1] || input[1] == "TMM")
		{
			_rep.E433(cUser.getFd(), cUser.getNick(), input[1]);
			return;
		}
	}
	if (cUser.getRegister())
	{
		_io.emit(":" + cUser.getNick() + " NICK " + input[1], cUser.getFd());
		cUser.setNick(input[1]);
		cUser.setUnusedNick(true);
		_rep.R001(cUser.getFd(), cUser.getNick());
		_rep.R002(cUser.getFd(), cUser.getNick(), "ScoobyIRC", "1.0");
		_rep.R003(cUser.getFd(), cUser.getNick(), _date);
		_rep.R004(cUser.getFd(), cUser.getNick());
		return ;
	}
	cUser.setNick(input[1]);
	cUser.setUnusedNick(true);
	for (std::vector<User>::iterator itUser = _clients.begin(); itUser != _clients.end(); itUser++)
		if (itUser->getNick() == cUser.getNick())
			itUser->setNick(input[1]);
	for (std::vector<Channel>::iterator itChan = _channels.begin(); itChan != _channels.end(); itChan++)
	{
		if (itChan->isUser(cUser))
		{
			std::vector<User> &chanUsers = itChan->getUsers();
			for (std::vector<User>::iterator itChanUser = chanUsers.begin(); itChanUser != chanUsers.end(); itChanUser++)
				if (itChanUser->getNick() == cUser.getNick())
					itChanUser->setNick(input[1]);
		}
		if (itChan->isOpUser(cUser))
		{
			std::vector<User> &chanOpUsers = itChan->getOpUsers();
			for (std::vector<User>::iterator itChanOpUser = chanOpUsers.begin(); itChanOpUser != chanOpUsers.end(); itChanOpUser++)
				if (itChanOpUser->getNick() == cUser.getNick())
					itChanOpUser->setNick(input[1]);
		}
	}
}
