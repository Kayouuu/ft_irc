/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/15 15:07:39 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <vector>
#include <ctime>
#include "User.hpp"
#include "SocketIO.hpp"

class SocketIO;
class User;

class Bot
{
	private:
		SocketIO	&_io;
		std::string	_scoob_msg;
		std::string	_velma_msg;
		std::string	_shaggy_msg;
		std::time_t _curr_time;
	public:
		Bot(SocketIO &io);
		~Bot();

		std::string const	&getMsg() const;
		void	check(std::vector<User> &clients);
		void	setMsg(std::string const &who, std::string const &new_msg);
		void	sendMsg(std::vector<User> &clients);
};



#endif
