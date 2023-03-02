/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/02 12:11:23 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <vector>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cerrno>
#include <cstdio>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>

#include <fcntl.h>
#include <unistd.h>

class Bot
{
	private:
		int						_port;
		std::string				_pass;
		std::string				_log_msg;
		bool					_isConnected;
		
		int						_socketFd;
		struct sockaddr_in 		_saddr;
		struct hostent 			*_local_host;
		std::string				_ip;

		std::time_t 			_curr_time;
		bool					_isChan;
		std::string				_currChannel;
		std::string				_possibleMsg;
		std::string				_announce_msg;

		std::string				_scoob_msg;
		std::string				_velma_msg;
		std::string				_shaggy_msg;
		std::string				_fred_msg;
		std::string				_daphne_msg;

		void	sendMsg();
		void	setChannel(std::string const &chanName);
		void	run();
		int		receive(std::string &output, int const &fd);
		void	emit(std::string const &input, int const &fd) const;
		void	handle(std::string const &output);
	public:
		Bot(int const &port, std::string const &pass, std::string const &ip);
		virtual ~Bot();

		void	start();
		void	shutdown();

		void	check();
		void	setMsg(std::vector<std::string> &input);
};



#endif
