/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/16 14:54:34 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

Bot::Bot(SocketIO &io) : _io(io)
{
	_scoob_msg = "You are in ScoobIRC, the best IRC server !";
	_velma_msg = "Jinkies!";
	_shaggy_msg = "Zoinks Scoob!";
	_curr_time = std::time(NULL);
}

Bot::~Bot() { }

void	Bot::setMsg(std::vector<std::string> &input, User &cUser)
{
	std::string::const_iterator msg_it;
	std::string	who = input[2];
	std::string	new_msg;

	std::vector<std::string>::iterator it = input.begin();
	it++; it++; it++;

	while (it != input.end())
	{
		new_msg.append(*it);
		if (++it != input.end() && *it != "")
			new_msg.append(" ");
	}
	if (new_msg == "")
		who = "";
    for (msg_it = new_msg.begin(); msg_it != new_msg.end(); ++msg_it)
    {
        if (!std::isspace(*msg_it))
			break ;
    }
	if (msg_it == new_msg.end())
		who = "";
	if (who == ":SCOOBY" || who == ":SCOOB" || who == ":SCOOBY-DOO")
		_scoob_msg = new_msg;
	else if (who == ":VELMA")
		_velma_msg = new_msg;
	else if (who == ":SHAGGY")
		_shaggy_msg = new_msg;
	else
	{
		_io.emit(":TheMysteryMachine NOTICE Usage => /msg TheMysteryMachine [SCOOBY, VELMA, SHAGGY] message ... ...", cUser.getFd());
		return ;
	}
	_io.emit(":TheMysteryMachine NOTICE " + cUser.getNick() + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", cUser.getFd());
}

void	Bot::check(std::vector<User> &clients)
{
	if (std::difftime(std::time(NULL), _curr_time) >= 300)
	{
		sendMsg(clients);
		_curr_time = std::time(NULL);
	}
}

void	Bot::sendMsg(std::vector<User> &clients)
{
	std::vector<User>::iterator it = clients.begin();
	std::string	scoob = ":SCOOBY-BOT NOTICE " + it->getNick() + " " + _scoob_msg;
	std::string	velma = ":VELMA NOTICE " + it->getNick() + " " + _velma_msg;
	std::string	shaggy = ":SHAGGY NOTICE " + it->getNick() + " " + _shaggy_msg;
	it++;
	for (it; it != clients.end(); it++)
	{
		if (it->getFd() != -1)
		{
			_io.emit(scoob, it->getFd());
			_io.emit(velma, it->getFd());
			_io.emit(shaggy, it->getFd());

		}
	}
}
