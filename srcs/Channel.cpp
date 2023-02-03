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
	return ;
}

const std::string &Channel::getName() const
{
	return _name;
}

const std::string &Channel::getSubject() const
{
	return _subject;
}

const std::__1::map<std::string, bool> &Channel::getMode() const
{
	return _mode;
}

const std::vector<User> &Channel::getUsers() const
{
	return _users;
}

void Channel::setName(const std::string &name)
{
	_name = name;
}

void Channel::setSubject(const std::string &subject)
{
	_subject = subject;
}

void Channel::setMode(const std::__1::map<std::string, bool> &mode)
{
	_mode = mode;
}

void Channel::setUsers(const std::vector<User> &users)
{
	_users = users;
}

Channel::~Channel()
{

}
