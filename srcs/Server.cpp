/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/30 15:00:50 by psaulnie         ###   ########.fr       */
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
	{
		std::cout << "socket: error" << std::endl;
		return (false);
	}
	if (fcntl(_server_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl: error" << std::endl;
		return (false);
	}
	// TOCOMMENT
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(this->_port);
	
	
	if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0) // TOCOMMENT + TODO explicit error msg
	{
		std::cout << "bind: error" << std::endl;
		return (false);
	}
	if (listen(this->_server_fd, 50) < 0) // TOCOMMENT + TODO explicit error msg
	{
		std::cout << "listen: error" << std::endl;
		return (false);
	}

	// Initializing the array of connected clients
	_clients.reserve(1024);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		_clients[i].setFd(-1);
	_clients[0].setFd(_server_fd);
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
			if (_clients[i].getFd() >= 0)
				FD_SET(_clients[i].getFd(), &read_fd_set); // Reading all the connected clients to the list
		returned_value = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
		if (returned_value < 0)
		{
			std::cout << "Error select" << returned_value << std::endl;
			// TODO Error msg + shutting down the server
			return (false);
		}

		if (FD_ISSET(_server_fd, &read_fd_set) && _connected_clients < MAX_CONNECTIONS) // If the _server_fd is triggered, new connection to the server
			acceptClient();
		else if (_connected_clients >= MAX_CONNECTIONS)
			std::cout << "Too many clients" << std::endl; // TOREPLACE with an err to the client ?
		for (int i = 1; i < MAX_CONNECTIONS; i++) // Checking on all connections if one is triggered
		{
			if (_clients[i].getFd() > 0 && FD_ISSET(_clients[i].getFd(), &read_fd_set))
				manageClient(i); // TODO manageClient function
		}
	}
	return (true);
}

bool	Server::acceptClient()
{
	// TODO putting the new user in an array of users
	int							new_connection;
	int							returned_value;
    std::string					tmp;
	User						tmp_user;

	new_connection = accept(_server_fd, (struct sockaddr *)&_address, &_addrlen); // TOCHECK cast
	
	if (new_connection < 0)
	{
		std::cout << "accept: failed to accept an incoming connection" << std::endl;
		return (false);
	}
	std::memset(_buffer, 0, 1024);
	while (recv(new_connection, &_buffer, 1024, 0))
	{
		tmp = _buffer;
		int	size;
		if ((size = tmp.find("NICK ", 0)) == 0)
			tmp_user.setNick(tmp.substr(5));
		if ((size = tmp.find("USER ", 0)) == 0)
		{
			tmp_user.setUser(tmp.substr(5, tmp.find(" ", 5) - 5));
			break ;
		}
	}

	std::string	msg = "001 " + tmp_user.getNick() + " :Welcome" + tmp_user.getNick() + " !";
	if (send(new_connection, msg.c_str(), strlen(msg.c_str()), 0) < 0)
	{
		std::cout << "send: error" << std::endl; // explicit msg
		return (false);
	}
	_clients.push_back(tmp_user);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		if (_clients[i].getFd() < 0)
			_clients[i].setFd(new_connection);
	_connected_clients++;
	return (true);
}

bool	Server::manageClient(int &current)
{
	// TODO array of function pointer for the commands, send()
	int		returned_value;

	returned_value = recv(_clients[current].getFd(), &_buffer, 1024, 0);

	if (returned_value == 0)
	{
		close(_clients[current].getFd());
		_clients[current].setFd(-1);
	}

	if (returned_value > 0)
	{
		_buffer[returned_value] = '\0';
		std::cout << _buffer << std::endl;
	}

	if (returned_value == -1)
	{
		// TODO error receiving
	}
	return (true);
}

