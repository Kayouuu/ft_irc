/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:44:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/02 14:43:16 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETIO_HPP
# define SOCKETIO_HPP

#include <sys/socket.h>
#include <iostream>
#include <cerrno>

class SocketIO
{
	public:
		SocketIO();
		~SocketIO();

		void	emit(std::string const &input, int fd) const;
		int		receive(std::string &output, int fd) const;
};

#endif