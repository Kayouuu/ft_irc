/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:44:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/13 10:54:58 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETIO_HPP
# define SOCKETIO_HPP

#include <sys/socket.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdio>

class SocketIO
{
	public:
		SocketIO();
		~SocketIO();

		void	emit(std::string const &input, int const &fd) const;
		int		receive(std::string &output, int const &fd);

};

#endif