/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 15:43:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password) { }

Server::~Server() { }

bool	Server::starting()
{
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0); // TOCOMMENT + TODO explicit error msg
	if (this->_server_fd < 0)
		return (false);
	// TOCOMMENT
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(this->_port);
	
	if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0) // TOCOMMENT + TODO explicit error msg
		return (false);

	if (listen(this->_server_fd, 3) < 0) // TOCOMMENT + TODO explicit error msg
		return (false);

	// Initializing the array of connected clients
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		_all_connections[i] = -1;
	_all_connections[0] = _server_fd;
}

bool	Server::run()
{
	// TODO While loop, fd_set, select(), receiving data or accepting new clients
	fd_set	read_fd_set;
	int		returned_value;

	std::cout << "The IRC server is running." << std::endl << "Waiting for connections..." << std::endl;

	while (1)
	{
		FD_ZERO(&read_fd_set); //  Cleaning the 
		for (int i = 0; i < MAX_CONNECTIONS; i++)
			if (_all_connections[i] >= 0)
				FD_SET(_all_connections[i], &read_fd_set);
		returned_value = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
		
	}
	
}

bool	Server::acceptClient()
{
	// TODO accept(), putting the new user in an array of users
}

bool	Server::manageClient()
{
	// TODO recv(), array of function pointer for the commands, send()
}