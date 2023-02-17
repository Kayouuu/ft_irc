/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/17 11:10:53 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() : _nick(""), _user(""), _prefix("") { _fd = -1; _right_password = false; _is_registered = false; _chanConnected = 0; }

User::User(const std::string &_nick, const std::string &_user)
{
	this->_nick = _nick;
	this->_user = _user;
	this->_right_password = false;
	this->_is_registered = false;
	this->_chanConnected = 0;
	_mode.insert(std::pair<char, bool>('i', false));
	_mode.insert(std::pair<char, bool>('s', false));
	_mode.insert(std::pair<char, bool>('w', false));
	_mode.insert(std::pair<char, bool>('o', false));
}

User::~User()
{
}

void User::setFd(int new_fd)
{
	_fd = new_fd;
}

void User::setNick(const std::string &nick)
{
	_nick = nick;
}

void User::setUser(const std::string &user)
{
	_user = user;	
}

void User::setPrefix(const std::string &prefix)
{
	_prefix = prefix;
}

void User::setMode(char const &modeName, bool const &isMode)
{
	std::map<char, bool>::iterator it = _mode.find(modeName);
	if (it == _mode.end())
		throw std::exception(); //TODO error msg
	it->second = isMode;
}

void	User::setRegister(bool const &input)
{
	_is_registered = input;
}

void	User::setRPassword(bool const &input)
{
	_right_password = input;
}


void User::addOpChannel(Channel &channel)
{
	_chanOp.push_back(channel);
}

void User::setIrcOp(bool ircOp)
{
	_ircOp = ircOp;
}

void User::incrChanConnected() {
	_chanConnected++;
}

int const &User::getFd() const
{
	return (_fd);
}	

std::string const &User::getNick() const
{
	return (_nick);
}

std::string const &User::getUser() const
{
	return (_user);
}

std::string const &User::getPrefix() const
{
	return (_prefix);
}

bool User::isMode(char mode)
{
	std::map<char, bool>::iterator it = _mode.find(mode);
	if (it == _mode.end())
		throw std::exception(); //TODO error msg
	return it->second;
}

std::string User::getModes()
{
	std::string modes;
	for (std::map<char, bool>::iterator mode = _mode.begin(); mode != _mode.end(); mode++)
	{
		if (mode->second)
			modes.append(&"+" [mode->first]);
	}
	std::cout << modes << std::endl;//TODO: to remove later, it's for debugging
	if (modes.empty())
		return "no modes yet";
	return modes;
}

std::vector<Channel> const &User::getOpChannels() const
{
	return _chanOp;
}

int const &User::getChanConnected() const {
	return _chanConnected;
}

bool User::isIrcOp() const
{
	return _ircOp;
}

User::User(const User &src)
{
	*this = src;
}

User &User::operator=(const User &rhs)
{
	_fd = rhs._fd;
	_nick = rhs._nick;
	_user = rhs._user;
	_prefix = rhs._prefix;
	_chanOp = rhs._chanOp;
	_ircOp = rhs._ircOp;
	return *this;
}

bool User::operator==(const User &rhs) const
{
	return _fd == rhs._fd &&
		   _nick == rhs._nick &&
		   _user == rhs._user &&
		   _prefix == rhs._prefix &&
		   _chanOp == rhs._chanOp &&
		   _ircOp == rhs._ircOp;
}

bool User::operator!=(const User &rhs) const
{
	return !(rhs == *this);
}

bool const &User::getRegister() const
{
	return (_is_registered);
}

bool const &User::getRPassword() const
{
	return (_right_password);
}

struct sockaddr_in	&User::getAdress()
{
	return (_address);
}

socklen_t			&User::getAdressLen()
{
	return (_addrlen);
}