/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:10:55 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/13 10:20:33 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::nickCmd(std::vector<std::string> &input, int fd, User &cUser) // TODO two other errors possible
{
	if (input[1].size() > 9)
	{
		std::cout << "Error: nickname is too long, 9 characters max\n"; // TOREPLACE with Error msg
		return;
	}
	std::vector<User>::iterator it = _clients.begin();
	for (it; it < _clients.end(); it++)
	{
		if (it->getNick() == input[1])
		{
			_rep.E433(fd, cUser.getNick(), input[1]);
			return;
		}
	}
	cUser.setNick(input[1]); //TOCHECK: set index 1 for the moment but review the input vector construction (wich index for the nickname)
}
