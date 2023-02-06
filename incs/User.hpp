/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:58:58 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/06 16:37:16 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <iostream>

class User
{
	private:
		int			_fd;
		std::string	_nick;
		std::string	_user;
		std::string	_prefix;
		bool		_is_registered;
		bool		_right_password;
	public:
		User();
		User(std::string _nick, std::string _user);
		virtual ~User();

		void	setFd(int new_fd);
		void	setNick(std::string	nick);
		void	setUser(std::string	user);
		void	setPrefix(std::string prefix);

		int const			&getFd() const;	
		std::string const	&getNick() const;
		std::string const	&getUser() const;
		std::string const	&getPrefix() const;
};

#endif