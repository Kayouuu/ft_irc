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

const std::map<std::string, bool> &Channel::getMode() const
{
	return _mode;
}

const std::vector<User> &Channel::getUsers() const
{
	return _users;
}

bool Channel::isBanned(User &user)
{
	//TODO
}

void Channel::setName(const std::string &name)
{
	_name = name;
}

void Channel::setSubject(const std::string &subject)
{
	_subject = subject;
}

void Channel::setMode(std::string &modeName, bool &isMode)
{
	//TODO;
}

void Channel::setUsers(User &users)
{
	//TODO;
}

void Channel::setOpUsers(User &opUsers)
{
	//TODO;
}

void Channel::banUser(User &user)
{
	//TODO
}

Channel::~Channel()
{

}
