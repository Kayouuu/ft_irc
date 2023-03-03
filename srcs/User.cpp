/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/02 11:44:06 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() : _nick(""), _user(""), _prefix("") { _fd = -1; _right_password = false; _is_registered = false; _chanConnected = 0; _unused_nick = false; _initConv = false; }

User::User(const std::string &nick, const std::string &user)
{
	_nick = nick;
	_user = user;
	_right_password = false;
	_is_registered = false;
	_unused_nick = false;
	_chanConnected = 0;
	_initConv = false;
	_ircOp = false;
	_mode.insert(std::pair<char, bool>('o', false));
	_mode.insert(std::pair<char, bool>('v', false));
}

User::~User()
{
	_mode.clear();
	_chanOp.clear();
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
		std::cout << "No mode " << modeName << std::endl; //TODO error msg
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

void	User::setUnusedNick(bool const &input)
{
	_unused_nick = input;
}

void User::addOpChannel(Channel &channel)
{
	_chanOp.push_back(channel);
}

void User::removeOpChannel(Channel &channel)
{
	std::vector<Channel>::iterator it = _chanOp.begin();
	for (; it < _chanOp.end(); it++)
	{
		if (*it == channel)
			_chanOp.erase(it);
	}
}

void User::addVoicedChan(Channel &voicedChan)
{
	_voicedChan.push_back(voicedChan);
}

void User::removeVoicedChannel(Channel &voicedChan)
{
	std::vector<Channel>::iterator it = _voicedChan.begin();
	for (; it < _voicedChan.end(); it++)
	{
		if (*it == voicedChan)
			_voicedChan.erase(it);
	}
}

void User::addInviteChan(Channel &inviteChan)
{
	_inviteChan.push_back(inviteChan);
}

void User::removeInviteChan(Channel &inviteChan)
{
	std::vector<Channel>::iterator it = _inviteChan.begin();
	for (; it < _inviteChan.end(); it++)
	{
		if (*it == inviteChan)
			_inviteChan.erase(it);
	}
}

void User::setIrcOp(bool ircOp)
{
	_ircOp = ircOp;
}

void User::incrChanConnected() {
	_chanConnected++;
}

void User::decrChanConnected() {
	_chanConnected--;
}
void User::resetUser() {
	std::map<char, bool>::iterator it = _mode.find('o');
	it->second = false;
	it = _mode.find('s');
	it->second = false;
	it = _mode.find('v');
	it->second = false;
	_voicedChan.clear();
	_inviteChan.clear();
	_chanOp.clear();
	_fd = -1;
	_nick = "";
	_prefix = "";
	_user = "";
	_is_registered = false;
	_right_password = false;
	_chanConnected = 0;
	_ircOp = false;
}

void User::setInitConv(bool value)
{
	_initConv = value;
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

bool const	&User::getUnusedNick() const
{
	return (_unused_nick);
}
		
bool User::isMode(char mode)
{
	std::map<char, bool>::iterator it = _mode.find(mode);
	if (it == _mode.end())
		std::cout << "No mode " << mode << std::endl; //TODO error msg
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

bool User::isChanOp(Channel &channel) {
	for (std::vector<Channel>::iterator it = _chanOp.begin(); it != _chanOp.end(); it++) {
		if (it->getName() == channel.getName())
			return true;
	}
	return false;
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
	_mode = rhs._mode;
	_voicedChan = rhs._voicedChan;
	_inviteChan = rhs._inviteChan;
	_chanOp = rhs._chanOp;
	_ircOp = rhs._ircOp;
	_is_registered = rhs._is_registered;
	_right_password = rhs._right_password;
	_unused_nick = rhs._unused_nick;
	_address = rhs._address;
	_addrlen = rhs._addrlen;
	_chanConnected = rhs._chanConnected;
	_initConv = rhs._initConv;
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

bool User::isVoicedChan(Channel &channel)
{
	for (std::vector<Channel>::iterator it = _voicedChan.begin(); it != _voicedChan.end(); it++)
	{
		if (it->getName() == channel.getName())
			return true;
	}
	return false;
}

bool User::isInviteChan(Channel &inviteChan)
{
	for (std::vector<Channel>::iterator it = _inviteChan.begin(); it != _inviteChan.end(); it++)
	{
		if (it->getName() == inviteChan.getName())
			return true;
	}
	return false;
}

bool User::isInitConv()
{
	return (_initConv);
}
