/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:07 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 13:36:12 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

Server::Server(int port, std::string password) : port(port), password(password) { }

Server::~Server() { }

bool	Server::starting()
{
	// socket(), bind(), init sockaddr_in, listen()
}

bool	Server::run()
{
	// While loop, fd_set, select(), receiving data or accepting new clients
}

bool	Server::acceptClient()
{
	// accept(), putting the new user in an array of users
}

bool	Server::manageClient()
{
	// recv(), array of function pointer for the commands, send()
}