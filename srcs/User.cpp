/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/09 17:38:09 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() : _nick(""), _user(""), _prefix("") { _fd = -1; _right_password = false; _is_registered = false; }

User::User(std::string _nick, std::string _user)
{
	this->_nick = _nick;
	this->_user = _user;
	this->_right_password = false;
	this->_is_registered = false;
}

User	&User::operator=(User const &other)
{
	_fd = other.getFd();
	_prefix.assign(other.getPrefix());
	_nick.assign(other.getNick());
	_user.assign(other.getUser());
	_right_password = other.getRPassword();
	_is_registered = other.getRegister();
	
	return (*this);
}

User::~User()
{
}

void	User::setFd(int const &new_fd)
{
	_fd = new_fd;
}
void	User::setNick(std::string const &nick)
{
	_nick = nick;
}
void	User::setUser(std::string const &user)
{
	_user = user;	
}
void	User::setPrefix(std::string const &prefix)
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


int const	&User::getFd() const
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
bool		const	&User::getRegister() const
{
	return (_is_registered);
}
bool		const	&User::getRPassword() const
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