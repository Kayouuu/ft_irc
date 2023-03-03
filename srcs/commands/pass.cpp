/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:34:30 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/03 13:44:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::passCmd(std::vector<std::string> &input, User &cUser)
{
	if (input.size() == 1)
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
	else if (input.size() > 1)
		cUser.setRPassword(input[1] == _password);
	else if (cUser.getRegister() == true)
		_rep.E462(cUser.getFd(), cUser.getNick());
	if (_password == input[1] && cUser.getRegister() == false && cUser.getUnusedNick() == true)
	{
		_rep.R001(cUser.getFd(), cUser.getNick());
		_rep.R002(cUser.getFd(), cUser.getNick(), "ScoobyIRC", "1.0");
		_rep.R003(cUser.getFd(), cUser.getNick(), _date);
		_rep.R004(cUser.getFd(), cUser.getNick());
		cUser.setRegister(true);
		if (_connected_clients == 1)
			_rep.R381(cUser.getFd(), cUser.getNick());
	}
}
