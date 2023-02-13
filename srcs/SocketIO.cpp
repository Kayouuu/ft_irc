/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:45:14 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/13 10:58:03 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketIO.hpp"

SocketIO::SocketIO() { }

SocketIO::~SocketIO() { }

void	SocketIO::emit(std::string const &input, int const &fd) const
{
	int error;

	std::cout << "Message sent: " << input;
	error = send(fd, input.c_str(), input.size(), 0);
	if (error < 0)
	{
		std::perror("send");
		throw std::exception();
	}		
}

int	SocketIO::receive(std::string &output, int const &fd)
{
	char	buffer[1024 + 1];
	int		rvalue;

	rvalue = recv(fd, &buffer, 1024, 0);
	if (rvalue < 0)
	{
		std::perror("recv");
		throw std::exception();
	}
	buffer[rvalue] = '\0';
	output.append(buffer);
	return (rvalue);
}

