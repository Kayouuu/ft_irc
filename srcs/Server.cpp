/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/08 18:29:53 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password), _rep(_io) { }

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

	int opt = 1;
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
	{
		std::cout << "setsocketopt: error" << std::endl;
		throw std::exception();
	}
	// TODO Check if needed to use setsocketopt() function (seems not)
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
	// _clients.reserve(MAX_CONNECTIONS);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		User	tmp_user = User();
		_clients.push_back(tmp_user);
	}
	_clients[0].setFd(_server_fd);

	char date_string[128];
	time_t curr_time;
	tm *curr_tm;
	_date = std::time(&curr_time);
	curr_tm = std::localtime(&curr_time);

	std::strftime(date_string, 50, "%c", curr_tm);

	_date = date_string;
}

/*
	Command init template:
		_commands.insert(ft::make_pair(std::string(""), &Server::)); 
*/
void	Server::initCommands()
{
	_commands.insert(std::make_pair(std::string("JOIN"), &Server::joinCmd));
	_commands.insert(std::make_pair(std::string("NICK"), &Server::nickCmd));
	_commands.insert(std::make_pair(std::string("PASS"), &Server::passCmd));
	_commands.insert(std::make_pair(std::string("USER"), &Server::userCmd));
}

void	Server::run()
{
	fd_set	read_fd_set;
	int		rvalue;

	std::cout << "The IRC server is running." << std::endl << "Waiting for connections..." << std::endl;
	while (1)
	{
		FD_ZERO(&read_fd_set); //  Cleaning the FD list & TOCOMMENT
		for (int i = 0; i < MAX_CONNECTIONS; i++)
			if (_clients[i].getFd() >= 0)
				FD_SET(_clients[i].getFd(), &read_fd_set); // Reading all the connected clients to the list
		// FD_SET(0, &read_fd_set);
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
	// std::memset(_buffer, 0, 1024);
	// while (recv(new_connection, &_buffer, 1024, 0))
	// {
	// 	tmp = _buffer;
	// 	int	size;
	// 	std::cout << tmp << std::endl; // TODO set password + send message if incorrect pass?
	// 	if ((size = tmp.find("NICK ", 0)) == 0)
	// 		tmp_user.setNick(tmp.substr(5));
	// 	if ((size = tmp.find("USER ", 0)) == 0)
	// 	{
	// 		tmp_user.setUser(tmp.substr(5, tmp.find(" ", 5) - 5));
	// 		break ;
	// 	}
	// }

	// std::string	msg = "001 " + tmp_user.getNick() + " :Welcome" + tmp_user.getNick() + " !";

	// std::cout << "New user logged: " << tmp_user.getNick() << std::endl; 
	// if (send(new_connection, msg.c_str(), strlen(msg.c_str()), 0) < 0)
	// {
	// 	std::cout << "send: error" << std::endl; // explicit msg
	// 	throw std::exception();
	// }
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		if (_clients[i].getFd() < 0)
		{
			_clients[i].setFd(new_connection);
			break ;
		}
	}
	_connected_clients++;
}

void	Server::manageClient(int &index)
{
	// TODO array of function pointer for the commands, send()
	int			rvalue;
	std::string	output;

	std::cout << "Triggered FD: " << _clients[index].getFd() << std::endl;

	rvalue = _io.receive(output, _clients[index].getFd());
	if (rvalue == 0)
	{
		// TODO reset string too
		close(_clients[index].getFd());
		_clients[index].setFd(-1);
		_clients[index].setNick("");
		_clients[index].setPrefix("");
		_clients[index].setUser("");
		_clients[index].setRegister(false);
		_clients[index].setRPassword(false);
		_connected_clients--;
	}
	if (rvalue > 0)
	{
		// std::cout << output << std::endl;
		commandHandler(output, _clients[index].getFd());
	}
}

void		Server::commandHandler(std::string const &output, int const &current) // TODO change output with input
{
	std::vector<std::string>	parsed_output;
	std::string					tmp;
	int							user_index;
	int							vector_it;
	int							size;

	for (user_index = 0; user_index < MAX_CONNECTIONS; user_index++)
		if (_clients[user_index].getFd() == current)
			break ;

	if (user_index == MAX_CONNECTIONS)
	{
		std::cout << "error: not finding the associated fd" << std::endl;
		throw std::exception();
	}

	for (size_t i = 0; i < output.length(); i++)
	{
		char c = output[i];
		if (std::isspace(c))
		{
			parsed_output.push_back(tmp);
			tmp.clear();
			vector_it++;
		}
		// else if (c == '\"')
		// {
		// 	tmp.push_back(c);
		// 	i++;
		// 	while (i < output.length() && output[i] != '\"') { tmp.push_back(c); i++; }
		// 	if (i < output.length())
		// 		tmp.push_back(c);
		// }
		else
		{
			tmp.push_back(c);
		}
	}
	std::cout << "Executed command: [" << parsed_output[0] << "]" << std::endl;
	if (_commands.find(parsed_output[0]) != _commands.end()) // TODO check if registered and not a command to login
		(this->*_commands[parsed_output[0]])(parsed_output, current, _clients[user_index]); // Execute command corresponding to the input
}
