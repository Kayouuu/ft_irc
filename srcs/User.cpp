/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/07 16:29:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() { _nick = ""; _user = ""; _fd = -1; _prefix = ""; _right_password = false; _is_registered = false; }

User::User(const std::string &_nick, const std::string &_user)
{
	this->_nick = _nick;
	this->_user = _user;
	this->_right_password = false;
	this->_is_registered = false;
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

std::vector<Channel> const &User::getOpChannels() const
{
	return _chanOp;
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
