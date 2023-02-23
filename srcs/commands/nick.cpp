/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:10:55 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/23 08:48:49 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::nickCmd(std::vector<std::string> &input, User &cUser)
{
	if (input[1] == "")
	{
		_rep.E431(cUser.getFd(), cUser.getNick());
		return ;
	}
	if (input[1].size() > 9) // TODO check unwanted character
	{
		_rep.E432(cUser.getFd(), cUser.getNick(), input[1]);
		return ;
	}
	std::vector<User>::iterator it = _clients.begin();
	for (it; it < _clients.end(); it++)
	{
		if (it->getNick() == input[1] || input[1] == "TheMysteryMachine")
		{
			cUser.setNick(input[1]);
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
	cUser.setNick(input[1]); //TOCHECK: set index 1 for the moment but review the input vector construction (wich index for the nickname) (?)
	cUser.setUnusedNick(true);
}
