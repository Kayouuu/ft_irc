/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:10:55 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/31 15:18:31 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::nickCmd(std::vector<std::string> input, int fd)
{
	if (input[1].size() > 9)
	{
		std::cout << "Error: nickname is too long, 9 characters max\n";
		return;
	}
	std::vector<User>::iterator it = _clients.begin();
	for (it; it < _clients.end(); it++)
	{
		if (it->getNick() == input[1])
		{
			std::cout << "Error: nickname already in use\n";//TODO FIX see NumericReplies.cpp to throw the correct error (Rep::E433)
			return;
		}
	}
	std::vector<User>::iterator ite = _clients.begin();
	for (ite; ite < _clients.end(); ite++)
	{
		if (ite->getFd() == fd)
			ite->setNick(input[1]);//TODO CHECK set index 1 for the moment but review the input vector construction (wich index for the nickname)
	}
	//TODO CHECK maybe throw a comment error if fd not found
}
