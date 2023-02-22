/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/22 17:09:48 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

Bot::Bot(SocketIO &io) : _io(io)
{
	_announce_msg = "---Bot conversation incoming---";
	_scoob_msg = "Ruh-roh--RAGGY!!!!";
	_shaggy_msg = "Zoinks Scoob!";
	_velma_msg = "Jinkies!";
	_daphne_msg = "Would you do it for a Scooby Snack?";
	_fred_msg = "Looks like we've got another mystery on our hands !";
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
	else if (who == ":FRED")
		_fred_msg = new_msg;
	else if (who == ":DAPHNE")
		_daphne_msg = new_msg;
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
	it++; // Skip the server fd
	for (it; it != clients.end(); it++)
	{
		if (it->getFd() != -1 && it->getRegister())
		{
			_io.emit(":TheMysteryMachine NOTICE " + it->getNick() + " " + _announce_msg, it->getFd());
			_io.emit(":SCOOBY-DOO NOTICE " + it->getNick() + " " + _scoob_msg, it->getFd());
			_io.emit(":VELMA NOTICE " + it->getNick() + " " + _velma_msg, it->getFd());
			_io.emit(":SHAGGY NOTICE " + it->getNick() + " " + _shaggy_msg, it->getFd());
			_io.emit(":DAPHNE NOTICE " + it->getNick() + " " + _daphne_msg, it->getFd());
			_io.emit(":FRED NOTICE " + it->getNick() + " " + _fred_msg, it->getFd());
		}
	}
}
