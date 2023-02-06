//
// Created by Delphine Bouron on 02/02/2023.
//

#include "../incs/Channel.hpp"

Channel::Channel()
{

}

Channel::Channel(const std::string &name, User &opUser) : _name(name)
{
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
	_mode.insert(std::pair<char, bool>('v', false));
}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel &Channel::operator=(const Channel &rhs)
{
	_name=rhs._name;
	_subject=rhs._subject;
	_mode=rhs._mode;
	_users=rhs._users;
	_opUsers=rhs._opUsers;
	_bannedUsers=rhs._bannedUsers;
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

bool Channel::getMode(char mode)
{
	std::map<char, bool>::iterator it = _mode.find(mode);
	if (it == _mode.end())
		throw std::exception(); //TODO error msg
	return it->second;
}

const std::vector<User> &Channel::getUsers() const
{
	return _users;
}

bool Channel::isBanned(User &user)
{
	for (std::vector<User>::iterator it = _bannedUsers.begin(); it < _bannedUsers.end(); it++)
	{
		if (user == *it)
			return true;
	}
	return false;
}

void Channel::setName(const std::string &name)
{
	_name = name;
}

void Channel::setSubject(const std::string &subject)
{
	_subject = subject;
}

void Channel::setMode(char &modeName, bool &isMode)
{
	std::map<char, bool>::iterator it = _mode.find(modeName);
	if (it == _mode.end())
		throw std::exception(); //TODO error msg
	it->second = isMode;
}

void Channel::addUser(User &user)
{
	_bannedUsers.push_back(user);
}

void Channel::addOpUser(User &opUser)
{
	_bannedUsers.push_back(opUser);
}

void Channel::banUser(User &user)
{
	_bannedUsers.push_back(user);
}

Channel::~Channel()
{

}
