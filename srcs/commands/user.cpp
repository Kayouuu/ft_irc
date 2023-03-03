/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:35:18 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/03 13:40:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::userCmd(std::vector<std::string> &input, User &cUser)
{
	if (input.size() < 5)
	{
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
		return ;
	}
	else if (cUser.getRegister() == true)
	{
		_rep.E462(cUser.getFd(), cUser.getNick());
		return ;
	}
	else if (cUser.getRPassword() == true && cUser.getUnusedNick() == true)
	{
		cUser.setUser(input[1]);
		cUser.setPrefix(input[4]);
		_rep.R001(cUser.getFd(), cUser.getNick());
		_rep.R002(cUser.getFd(), cUser.getNick(), "ScoobyIRC", "1.0");
		_rep.R003(cUser.getFd(), cUser.getNick(), _date);
		_rep.R004(cUser.getFd(), cUser.getNick());
	}
	if (cUser.getRPassword() == true)
	{
		cUser.setRegister(true);
		if (_connected_clients == 1)
			_rep.R381(cUser.getFd(), cUser.getNick());
	}
}
