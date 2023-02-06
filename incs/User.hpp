/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:58:58 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/30 14:52:02 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <vector>
# include "Channel.hpp"

class User
{
	private:
		int						_fd;
		std::string				_nick;
		std::string				_user;
		std::string				_prefix;
		std::vector<Channel>	_chanOp;//array of channels in which the user is operator
		bool					_ircOp;//true: user is irc operator, false: user is not irc operator

	public:
		User();
		User(const std::string &_nick, const std::string& _user);
		User(const User &src);
		virtual ~User();

		User &operator=(const User &rhs);
		bool operator==(const User &rhs) const;
		bool operator!=(const User &rhs) const;

		void	setFd(int new_fd);
		void	setNick(const std::string &nick);
		void	setUser(const std::string &user);
		void	setPrefix(const std::string &prefix);
		void	addOpChannel(Channel &channel);
		void	setIrcOp(bool ircOp);

		int const					&getFd() const;
		std::string const			&getNick() const;
		std::string const			&getUser() const;
		std::string const			&getPrefix() const;
		std::vector<Channel> const	&getOpChannels() const;
		bool 						isIrcOp() const;
};

#endif