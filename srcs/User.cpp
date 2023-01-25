/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:00:21 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 13:31:31 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

User::User() { }

User::User(std::string _nick, std::string _user)
{
	this->_nick = _nick;
	this->_user = _user;
}

User::~User()
{
}

void	User::setNick(std::string nick)
{
	_nick = nick;
}
void	User::setUser(std::string user)
{
	_user = user;	
}
void	User::setPrefix(std::string prefix)
{
	_prefix = prefix;
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