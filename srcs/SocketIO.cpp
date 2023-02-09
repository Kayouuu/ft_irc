/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:45:14 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:03 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketIO.hpp"

SocketIO::SocketIO() { }

SocketIO::~SocketIO() { }

void	SocketIO::emit(std::string const &input, int const &fd) const
{
	int error;
	// std::cout << input.size() << std::endl;
	// std::cout << send(fd, "001 pierrot :Welcome to the Internet Relay Network pierrot", 44, 0) << std::endl;
	std::cout << "Message sent: " << input;
	error = send(fd, input.c_str(), input.size(), 0);
	if (error < 0)
	{
		std::cout << "send: error" << std::endl; // TODO explicit msg
		throw std::exception();
	}		
}

int	SocketIO::receive(std::string &output, int const &fd) const
{
	char	buffer[1024 + 1];
	int		rvalue;

	rvalue = recv(fd, &buffer, 1024, 0);
	if (rvalue < 0)
	{
		std::cout << "recv: error" << std::endl; // TODO explicit msg
		throw std::exception();
	}
	buffer[rvalue] = '\0';
	output = buffer;
	return (rvalue);
}

