/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:31:44 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/01 16:59:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

int	main(int argc, char *argv[])
{
	int			port;
	char		*ip = argv[1];
	char		*password = argv[3];

	if (argc != 4)
	{
		std::cout << "Usage: ./ircserv [ip] [port] [password]" << std::endl;
		return (-1);
	}
	for (int i = 0; argv[2][i]; i++)
	{
		if (!std::isdigit(argv[2][i]))
		{
			std::cout << "First parameter must be a number between 0 and 65535" << std::endl;
			return (1);
		}
	}
	port = std::atoi(argv[2]); // TOREPLACE with std::strtol ((int)strtol(s, &stopped, 10); if (*stopped) { /* handle error */ })
	if (port < 0 || port > 65535)
	{
		std::cout << "Port range must be between 0 and 65535" << std::endl;
		return (-1);
	}

	Bot			bot(port, password, ip);
	
	try
	{
		bot.start();
	}
	catch(const std::exception& e)
	{
		bot.shutdown();
		std::cerr << e.what() << '\n';
	}	
}
