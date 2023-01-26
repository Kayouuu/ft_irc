/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/26 16:53:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password) { }

Server::~Server() { }

bool	Server::starting()
{
	_connected_clients = 0;
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0); // TOCOMMENT + TODO explicit error msg
	if (this->_server_fd < 0)
		return (false);
	std::cout << "salut" << std::endl;
	// TOCOMMENT
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(this->_port);
	
	if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0) // TOCOMMENT + TODO explicit error msg
		return (false);

	if (listen(this->_server_fd, 50) < 0) // TOCOMMENT + TODO explicit error msg
		return (false);

	// Initializing the array of connected clients
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		_all_connections[i] = -1;
	_all_connections[0] = _server_fd;
	return (true);
}

bool	Server::run()
{
	// TODO While loop, fd_set, select(), receiving data or accepting new clients
	fd_set	read_fd_set;
	int		returned_value;

	std::cout << "The IRC server is running." << std::endl << "Waiting for connections..." << std::endl;

	while (1)
	{
		FD_ZERO(&read_fd_set); //  Cleaning the FD list & TOCOMMENT
		for (int i = 0; i < MAX_CONNECTIONS; i++)
			if (_all_connections[i] >= 0)
				FD_SET(_all_connections[i], &read_fd_set); // Reading all the connected clients to the list
		returned_value = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
		if (returned_value < 0)
		{
			// TODO Error msg + shutting down the server
			return (false);
		}

		if (FD_ISSET(_server_fd, &read_fd_set) && _connected_clients < MAX_CONNECTIONS) // If the _server_fd is triggered, new connection to the server
			acceptClient();
		else if (_connected_clients >= MAX_CONNECTIONS)
			std::cout << "Too many clients" << std::endl; // TOREPLACE with an err to the client ?
		for (int i = 1; i < MAX_CONNECTIONS; i++) // Checking on all connections if one is triggered
		{
			if (_all_connections[i] > 0 && FD_ISSET(_all_connections[i], &read_fd_set))
				manageClient(i); // TODO manageClient function
		}
	}
	return (true);
}

bool	Server::acceptClient()
{
	// TODO putting the new user in an array of users
	int			new_connection;
	int			returned_value;
	char		buffer[1024]; // TOREPLACE

	new_connection = accept(_server_fd, (struct sockaddr *)&_address, &_addrlen); // TOCHECK cast
	
	if (new_connection < 0)
	{
		std::cout << "accept: failed to accept an incoming connection" << std::endl;
		return (false);
	}

	for (int i = 0; i < MAX_CONNECTIONS; i++)
		if (_all_connections[i] < 0)
			_all_connections[i] = new_connection;
	_connected_clients++;
	return (true);
}

bool	Server::manageClient(int &current)
{
	// TODO array of function pointer for the commands, send()
	int		returned_value;
	char	buffer[1024]; // TOREPLACE

	returned_value = recv(_all_connections[current], &buffer, 1024, 0);
	
	if (returned_value == 0)
	{
		close(_all_connections[current]);
		_all_connections[current] = -1;
	}

	if (returned_value > 0)
	{
		buffer[returned_value] = '\0';
		std::cout << buffer << std::endl;
	}

	if (returned_value == -1)
	{
		// TODO error receiving
	}
	return (true);
}

