/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:45:14 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/13 09:58:43 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/SocketIO.hpp"

SocketIO::SocketIO() { }

SocketIO::~SocketIO() { }

void	SocketIO::emit(std::string const &input, int const &fd) const
{
	std::string	msg = input + "\r\n";
	int 		error;

	std::cout << "Message sent: " << input << std::endl;
	error = send(fd, msg.c_str(), msg.size(), 0);
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
	int		loop_exit; 

	while (1)
	{
		std::memset(&buffer, 1, 1024);
		rvalue = recv(fd, &buffer, 1024, 0);
		if (buffer[rvalue] == 0 || rvalue == 0)
			break ;
		if (rvalue < 0)
		{
			std::perror("recv");
			throw std::exception();
		}
		buffer[rvalue] = '\0';
		output.append(buffer);
		loop_exit = output.find(10);
		if (loop_exit >= 0 || loop_exit <= output.size())
			break ;
	}
	return (rvalue);
}
	
