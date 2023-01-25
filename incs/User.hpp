/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:58:58 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 15:25:48 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class User
{
	private:
		std::string	_nick;
		std::string	_user;
		std::string	_prefix;
	public:
		User();
		User(std::string _nick, std::string _user);
		virtual ~User();

		void	setNick(std::string	nick);
		void	setUser(std::string	user);
		void	setPrefix(std::string prefix);

		std::string const &getNick() const;
		std::string const &getUser() const;
		std::string const &getPrefix() const;
};
