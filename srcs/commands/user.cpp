/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:35:18 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/09 11:37:05 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::userCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
	std::cout << "FD sent to USER cmd: " << cUser.getFd() << std::endl;
	if (input.size() < 5)
		_rep.E461(fd, cUser.getNick(), input[0]);
	else if (cUser.getRegister() == true)
		_rep.E462(fd, cUser.getNick());
	else if (cUser.getRPassword() == true)
	{
		cUser.setUser(input[1]);
		cUser.setPrefix(input[4]);
		cUser.setRegister(true);
		_rep.R001(cUser.getFd(), cUser.getNick());
		_rep.R002(cUser.getFd(), cUser.getNick(), "ScoobyIRC", "1.0");
		_rep.R003(cUser.getFd(), cUser.getNick(), _date);
	}
}
