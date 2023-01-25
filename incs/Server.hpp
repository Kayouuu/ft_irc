/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:00 by psaulnie          #+#    #+#             */
/*   Updated: 2023/01/25 15:44:26 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <iostream>

#define MAX_CONNECTIONS	1024

class Server
{
	// TODO Users array	(vector) + function getUserByNickname()
	// TODO Channel class + Channel array (vector)

	private:
		int					_server_fd;
		int					_all_connections[MAX_CONNECTIONS];
		struct sockaddr_in	_address;
		const int			_port;
		const std::string	_password;

		bool	acceptClient();
		bool	manageClient();
	public:
		Server(int port, std::string password);
		~Server();

		bool	starting();
		bool	run();
	

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