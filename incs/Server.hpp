/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:00 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 13:29:27 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define MAX_CONNECTIONS	1024

class Server
{
private:
	int					server_fd;
	int					all_connections[MAX_CONNECTIONS];
	fd_set				fdset;
	struct sockaddr_in	address;

	const int			port;
	const std::string	password;
public:
	Server(int port, std::string password);
	~Server();

	bool	starting();
	bool	run();
	bool	acceptClient();
	bool	manageClient();
	

};

/*

Server algorithm:

1-Use of socket and bind, init sockaddr_in struct, listen in a "start" function
2-While loop
	a.Clear fdset and reinit all the clients in it 
	  (used by select to check all the clients that need to be checked, 
	  cf. codingbison tuto)
	b.Use select() to listen for incoming events
	c.select will identify the fd that has events :
		-If it's the server fd, then we can accept a new client
		-If it's another fd(except -1 that will cause to break to loop
	    and exit the program), then we can manage the client associated with the fd
	    and using recv to get what they send and eventually send them datas
	d.Looping

*/

#endif