/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:45:14 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/31 14:27:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketIO.hpp"

SocketIO::SocketIO() { }

SocketIO::~SocketIO() { }

void	SocketIO::emit(std::string const &input, int fd) const
{
	if (send(fd, input.c_str(), input.length(), 0) < 0)
	{
		std::cout << "send: error" << std::endl; // TODO explicit msg
		throw std::exception();
	}		
}

int	SocketIO::receive(std::string &output, int fd) const
{
	char	buffer[1024];
	int		rvalue;

	rvalue = recv(fd, &buffer, 1024, 0);
	if (rvalue < 0)
	{
		std::cout << "recv: error" << std::endl; // TODO explicit msg
		throw std::exception();
	}
	output = buffer;
	return (rvalue);
}
