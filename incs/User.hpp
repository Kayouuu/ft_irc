/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:58:58 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/14 16:29:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <vector>
# include "Channel.hpp"
# include <netinet/in.h>
// #include "Server.hpp"

class Channel;

class User
{
	private:
		int						_fd;
		std::string				_nick;
		std::string				_user;
		std::string				_prefix;
		std::map<char, bool>	_mode;
		std::vector<Channel>	_chanOp;//array of channels in which the user is operator
		bool					_ircOp;//true: user is irc operator, false: user is not irc operator
		bool					_is_registered;
		bool					_right_password;
		struct sockaddr_in		_address;
		socklen_t				_addrlen;
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
		bool	isMode(char mode);
		void	addOpChannel(Channel &channel);
		void	setIrcOp(bool ircOp);
		void	setRegister(bool const &input);
		void	setRPassword(bool const &input);

		int const					&getFd() const;
		std::string const			&getNick() const;
		std::string const			&getUser() const;
		std::string const			&getPrefix() const;
		void 						setMode(char &modeName, bool &isMode);
		std::vector<Channel> const	&getOpChannels() const;
		bool 						isIrcOp() const;
		bool const					&getRegister() const;
		bool const					&getRPassword() const;
		struct sockaddr_in			&getAdress();
		socklen_t					&getAdressLen();
};

#endif
