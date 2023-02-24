/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/24 11:26:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

Bot::Bot(SocketIO &io, std::vector<Channel> &channels) : _io(io), _channels(channels), _isChan(false)
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
	else if (who == ":CHANNEL" && input[4] != "")
	{
		setChannel(input[3], cUser);
		return ;
	}
	else
	{
		_io.emit(":TheMysteryMachine PRIVMSG " + cUser.getNick() + " Usage => /msg TheMysteryMachine [SCOOBY, VELMA, SHAGGY, DAPHNE, FRED, CHANNEL] [message, #channelname] {...} {...}", cUser.getFd());
		return ;
	}
	_io.emit(":TheMysteryMachine PRIVMSG " + cUser.getNick() + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", cUser.getFd());
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
	std::vector<Channel>::iterator it;

	if (_currChannel == "")
		return ;
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if (_currChannel == it->getName())
			break ;
	}
	std::vector<User>			users = it->getUsers();
	std::vector<User>::iterator itUsers = clients.begin();
	for (itUsers; itUsers != clients.end(); itUsers++)
	{
		if (itUsers->getFd() != -1 && itUsers->getRegister() && itUsers->getRPassword())
		{
			_io.emit(":TheMysteryMachine PRIVMSG " + it->getName() + " " + _announce_msg, itUsers->getFd());
			_io.emit(":SCOOBY-DOO PRIVMSG " + it->getName() + " " + _scoob_msg, itUsers->getFd());
			_io.emit(":VELMA PRIVMSG " + it->getName() + " " + _velma_msg, itUsers->getFd());
			_io.emit(":SHAGGY PRIVMSG " + it->getName() + " " + _shaggy_msg, itUsers->getFd());
			_io.emit(":DAPHNE PRIVMSG " + it->getName() + " " + _daphne_msg, itUsers->getFd());
			_io.emit(":FRED PRIVNSG " + it->getName() + " " + _fred_msg, itUsers->getFd());
		}
	}
	users.clear();
}

void	Bot::setChannel(std::string const &chanName, User &cUser)
{
	std::vector<Channel>::iterator it;

	if (!cUser.isIrcOp())
	{
		_io.emit(":TheMysteryMachine PRIVMSG " + cUser.getNick() + " You need to be the IRC operator!", cUser.getFd());
		return ;
	}
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		std::cout << chanName << std::endl;
		if (chanName == it->getName())
			break ;
	}
	if (it == _channels.end())
	{
		_io.emit(":TheMysteryMachine PRIVMSG " + cUser.getNick() + " There is no such channel!", cUser.getFd());
		return ;
	}
	_io.emit(":TheMysteryMachine PRIVMSG " + it->getName() + " Bot will send messages here!", cUser.getFd());

	_currChannel = chanName;
}
