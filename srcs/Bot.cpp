/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/14 16:40:06 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

Bot::Bot(SocketIO &io) : _io(io), _msg("You are in ScoobIRC, the best IRC server !")
{
	_curr_time = std::time(NULL);
}

Bot::~Bot() { }

std::string const	&Bot::getMsg() const
{
	return (_msg);
}

void	Bot::setMsg(std::string const &new_msg)
{
	_msg = new_msg;
}

void	Bot::check(std::vector<User> &clients)
{
	double rvalue;
	if ((rvalue = std::difftime(std::time(NULL), _curr_time)) >= 10)
	{
		sendMsg(clients);
		_curr_time = std::time(NULL);
	}
	std::cout << rvalue << std::endl;
}

void	Bot::sendMsg(std::vector<User> &clients)
{
	for (std::vector<User>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->getFd() != -1)
		{
			_io.emit(_msg, it->getFd());
		}
	}
}
