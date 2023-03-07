/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:44:15 by dbouron           #+#    #+#             */
/*   Updated: 2023/03/07 13:38:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

Channel::Channel() {}

Channel::~Channel()
{
	_users.clear();
	_opUsers.clear();
	_bannedUsers.clear();
	_mode.clear();
}

Channel::Channel(const std::string &name, User &opUser) : _name(name), _usrNbMax(MAX_CONNECTIONS), _usrCon(1), _pw(""), _isTopic(false)
{
	_users.insert(_users.begin(), opUser);
	_opUsers.insert(_opUsers.begin(), opUser);
	_mode.insert(std::pair<char, bool>('i', false));
	_mode.insert(std::pair<char, bool>('k', false));
	_mode.insert(std::pair<char, bool>('l', false));
	_mode.insert(std::pair<char, bool>('m', false));
	_mode.insert(std::pair<char, bool>('n', false));
	_mode.insert(std::pair<char, bool>('p', false));
	_mode.insert(std::pair<char, bool>('r', false));
	_mode.insert(std::pair<char, bool>('s', false));
	_mode.insert(std::pair<char, bool>('t', false));
}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel &Channel::operator=(const Channel &rhs)
{
	_name=rhs._name;
	_subject=rhs._subject;
	_isTopic=rhs._isTopic;
	_mode=rhs._mode;
	_users=rhs._users;
	_opUsers=rhs._opUsers;
	_bannedUsers=rhs._bannedUsers;
	_usrNbMax=rhs._usrNbMax;
	_usrCon=rhs._usrCon;
	_pw=rhs._pw;
	return *this;
}

const std::string &Channel::getName() const
{
	return _name;
}

const std::string &Channel::getSubject() const
{
	return _subject;
}

bool Channel::isMode(char mode)
{
	std::map<char, bool>::iterator it = _mode.find(mode);
	if (it == _mode.end())
		return false;
	return it->second;
}

std::string Channel::getModes()
{
	std::string modes;
	for (std::map<char, bool>::iterator mode = _mode.begin(); mode != _mode.end(); mode++)
	{
		if (mode->second)
		{
			std::string letter;
			letter.append(1, mode->first);
			modes.append("+" + letter);
		}
	}
	return modes;
}

std::vector<User> &Channel::getUsers()
{
	return _users;
}

std::vector<User> &Channel::getOpUsers()
{
	return _opUsers;
}

bool Channel::isUser(User &user)
{
	for (std::vector<User>::iterator it = _users.begin(); it < _users.end(); it++)
	{
		if (user.getNick() == it->getNick())
			return true;
	}
	return false;
}

bool Channel::isOpUser(User &user)
{
	for (std::vector<User>::iterator it = _opUsers.begin(); it < _opUsers.end(); it++)
	{
		if (user.getNick() == it->getNick())
			return true;
	}
	return false;
}

bool Channel::isBanned(User &user)
{
	for (std::vector<User>::iterator it = _bannedUsers.begin(); it < _bannedUsers.end(); it++)
	{
		if (user.getNick() == it->getNick())
			return true;
	}
	return false;
}

const std::string Channel::getPw() const  
{
	return _pw;	
}

unsigned short Channel::getUsrCon() const
{
	return _usrCon;
}

unsigned short Channel::getUsrNbMax() const 
{
	return _usrNbMax;
}

bool Channel::getIsTopic() const
{
	return _isTopic;	
}

char Channel::getChanPrefix()
{
	if 	(isMode('s') == true)
		return '@';
	else if (isMode('p') == true)
		return '*';
	return '=';
}

char Channel::getUserPrefix(User &cUser)
{
	std::vector<User>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNick() == cUser.getNick())
			break;
	}
	if (it == _users.end())
		return 'u';
	if (isOpUser(*it)) {
		return '@';
	}
	if (it->isMode('v')) {
		if (it->isVoicedChan(*this))
			return '+';
	}
	return 'u';
}

void Channel::setSubject(const std::string &subject)
{
	_subject = subject;
	setIsTopic(true);
}

void Channel::setMode(char const &modeName, bool const &isMode)
{
	std::map<char, bool>::iterator it = _mode.find(modeName);
	if (it == _mode.end())
		return ;
	it->second = isMode;
}

void Channel::addUser(User &user)
{
	_users.push_back(user);
}

void Channel::removeUser(User &user)
{
	std::vector<User>::iterator it = _users.begin();
	for (it; it < _users.end(); it++)
	{
		if (it->getNick() == user.getNick())
			_users.erase(it);
	}
}

void Channel::removeOpUser(User &user)
{
	std::vector<User>::iterator it = _opUsers.begin();
	for (it; it < _opUsers.end(); it++)
	{
		if (it->getNick() == user.getNick())
			_opUsers.erase(it);
	}
}

void Channel::addOpUser(User &opUser)
{
	_opUsers.push_back(opUser);
	// opUser.setMode('v', true); TODO check if needed
}

void Channel::banUser(User &user)
{
	_bannedUsers.push_back(user);
}

void Channel::unbanUser(User &user)
{
	for (std::vector<User>::iterator it = _bannedUsers.begin(); it != _bannedUsers.end(); it++)
	{
		if (it->getFd() == user.getFd())
		{	
			_bannedUsers.erase(it);
			break ;
		}
	}
}

void Channel::listBannedUser(Rep &rep, User const &cUser)
{
	for (std::vector<User>::iterator it = _bannedUsers.begin(); it != _bannedUsers.end(); it++)
	{
		rep.R367(cUser.getFd(), cUser.getNick(), this->getName(), it->getNick());
	}
	rep.R368(cUser.getFd(), cUser.getNick(), this->getName());
}

void Channel::setPw(std::string pw)
{
	_pw = pw;
}

void Channel::incrUsrCon()
{
	_usrCon++;
}

void Channel::decrUsrCon()
{
	_usrCon--;
}

void Channel::setUsrNbMax(unsigned short nbr)
{
	_usrNbMax = nbr;	
}

void Channel::setIsTopic(bool status)
{
	_isTopic = status;
}

bool Channel::operator==(const Channel &rhs) const
{
	return _name == rhs._name &&
		   _subject == rhs._subject &&
		   _mode == rhs._mode &&
		   _users == rhs._users &&
		   _opUsers == rhs._opUsers &&
		   _bannedUsers == rhs._bannedUsers &&
		   _usrNbMax == rhs._usrNbMax &&
		   _pw == rhs._pw;
}

bool Channel::operator!=(const Channel &rhs) const
{
	return !(rhs == *this);
}
