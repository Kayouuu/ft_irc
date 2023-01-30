/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:12:10 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/26 17:05:29 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

int main(int argc, char *argv[])
{
	int	port;
	char *err;

	if (argc != 3)
	{
		std::cout << "Usage: ./ft_irc [port] [password]" << std::endl;
		return (-1);
	}

	port = (int)std::strtol(argv[1], &err, 10);
	if (*err) { /* handle error */ } //TODO handle error
	if (port < 0 || port > 65535)
	{
		std::cout << "Port range must be between 0 and 65535" << std::endl;
		return (-1);
	}

	Server	server(port, argv[2]);
	if (!server.starting())
	{
		std::cout << "" << std::endl;
		return (-1);
	}
	if (!server.run())
	{
		std::cout << "" << std::endl;
		return (-1);
	}
	std::cout << "Shutting down the server" << std::endl;
	return (0);
}
