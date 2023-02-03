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

class User
{
	private:
	int								_fd;
		std::string					_nick;
		std::string					_user;
		std::string					_prefix;
		std::vector<std::string>	_chanOp;//true: user is channel operator, false: user is not channel operator
		bool						_ircOp;//true: user is irc operator, false: user is not irc operator

	public:
		User();
		User(const std::string &_nick, const std::string& _user);
		virtual ~User();

		void	setFd(int new_fd);
		void	setNick(const std::string &nick);
		void	setUser(const std::string &user);
		void	setPrefix(const std::string &prefix);
		void	setOp(bool op);

		int const			&getFd() const;	
		std::string const	&getNick() const;
		std::string const	&getUser() const;
		std::string const	&getPrefix() const;
		bool 				isOp() const;
};

#endif