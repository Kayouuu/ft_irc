/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/02 15:36:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password) { }

Server::~Server() { }

void	Server::starting()
{
	_connected_clients = 0;
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0); // TOCOMMENT + TODO explicit error msg
	if (this->_server_fd < 0)
	{
		std::cout << "socket: error" << std::endl;
		throw std::exception();
	}
	// if (fcntl(_server_fd, F_SETFL, O_NONBLOCK) == -1)
	// {
	// 	std::cout << "fcntl: error" << std::endl;
	// 	return (false);
	// }
	// TOCOMMENT
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(this->_port);
	
	
	if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0) // TOCOMMENT + TODO explicit error msg
	{
		std::cout << "bind: error" << std::endl;
		throw std::exception();
	}
	if (listen(this->_server_fd, 50) < 0) // TOCOMMENT + TODO explicit error msg
	{
		std::cout << "listen: error" << std::endl;
		throw std::exception();
	}

	initCommands(); // TODO check errors ?

	// Initializing the array of connected clients
	_clients.reserve(MAX_CONNECTIONS);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		_clients[i].setFd(-1);
	_clients[0].setFd(_server_fd);
}

/*
	Command init template:
		_commands.insert(ft::make_pair(std::string(""), &Server::)); 
*/
void	Server::initCommands()
{
	_commands.insert(std::make_pair(std::string("JOIN"), &Server::joinCmd));
	_commands.insert(std::make_pair(std::string("NICK"), &Server::nickCmd));
}

void	Server::run()
{
	fd_set	read_fd_set;
	int		rvalue;

	std::cout << "The IRC server is running." << std::endl << "Waiting for connections..." << std::endl;
	signal(SIGINT, Server::stop);
	while (1)
	{
		FD_ZERO(&read_fd_set); //  Cleaning the FD list & TOCOMMENT
		for (int i = 0; i < MAX_CONNECTIONS; i++)
		{
			if (_clients[i].getFd() >= 0)
			{
				// std::cout << i << " " << _clients[i].getFd() << std::endl;
				int fd = _clients[i].getFd(); // TODO maybe put the fd in another array anyway lool xD nyahh
				FD_SET(fd, &read_fd_set); // Reading all the connected clients to the list
				_clients[i].setFd(fd);
			}
		}
		FD_SET(0, &read_fd_set);
		rvalue = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
		if (rvalue < 0)
		{
			std::cout << errno << std::endl;
			std::cout << "select: error" << std::endl;
			// TODO Error msg + shutting down the server
			throw std::exception();
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
}

void	Server::acceptClient()
{
	// TODO putting the new user in an array of users
	int							new_connection;
    std::string					tmp;
	User						tmp_user;

	new_connection = accept(_server_fd, (struct sockaddr *)&_address, &_addrlen); // TOCHECK cast
	
	if (new_connection < 0)
	{
		std::cout << "accept: failed to accept an incoming connection" << std::endl;
		throw std::exception();
	}
	std::memset(_buffer, 0, 1024);
	while (recv(new_connection, &_buffer, 1024, 0))
	{
		tmp = _buffer;
		int	size;
		std::cout << tmp << std::endl; // TODO set password + send message if incorrect pass?
		if ((size = tmp.find("NICK ", 0)) == 0)
			tmp_user.setNick(tmp.substr(5));
		if ((size = tmp.find("USER ", 0)) == 0)
		{
			tmp_user.setUser(tmp.substr(5, tmp.find(" ", 5) - 5));
			break ;
		}
	}

	std::string	msg = "001 " + tmp_user.getNick() + " :Welcome" + tmp_user.getNick() + " !";

	std::cout << "New user logged: " << tmp_user.getNick() << std::endl; 
	
	if (send(new_connection, msg.c_str(), strlen(msg.c_str()), 0) < 0)
	{
		std::cout << "send: error" << std::endl; // explicit msg
		throw std::exception();
	}
	_clients.push_back(tmp_user);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		if (_clients[i].getFd() < 0)
			_clients[i].setFd(new_connection);
	}
	_connected_clients++;
}

void	Server::manageClient(int &current)
{
	// TODO array of function pointer for the commands, send()
	int			rvalue;
	std::string	output;

	rvalue = _io.receive(output, _clients[current].getFd());

	if (rvalue == 0)
	{
		close(_clients[current].getFd());
		_clients[current].setFd(-1);
		_connected_clients--;
	}

	if (rvalue > 0)
	{
		std::cout << output << std::endl;
		if (output.find("PING"))
			_io.emit("PONG 127.0.0.1", _clients[current].getFd());
	}

}

void	Server::stop(int signal)
{
	
}
