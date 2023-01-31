/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:44:22 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/31 15:08:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETIO_HPP
# define SOCKETIO_HPP

#include <sys/socket.h>
#include <iostream>

class SocketIO
{
	public:
		SocketIO();
		~SocketIO();

		void	emit(std::string const &input, int fd) const;
		int		receive(std::string &output, int fd) const;
};

#endif