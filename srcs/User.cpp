/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/30 14:53:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() { }

User::User(const std::string &_nick, const std::string &_user)
{
	this->_nick = _nick;
	this->_user = _user;
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
	_fd = src._fd;
	_nick = src._nick;
	_user = src._user;
	_prefix = src._prefix;
	_chanOp = src._chanOp;
	_ircOp = src._ircOp;
}

User &User::operator=(const User &rhs)
{
	*this = rhs;
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
