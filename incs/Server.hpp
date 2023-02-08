/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:00 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/08 14:04:46 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/select.h>
# include <unistd.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <iostream>
# include <vector>
# include <map>

# include <csignal>
# include <cstring>
# include <cerrno>
# include <cstdlib>

# include "User.hpp"
# include "SocketIO.hpp"
# include "Channel.hpp"
# include "NumericReplies.hpp"

# define MAX_CONNECTIONS	1024

class	SocketIO;
class	Rep;

class Server
{
	// function getUserByNickname()

	private:
		typedef	void (Server::*cmdHandler)(std::vector<std::string> const &, int, User &); // Array of function pointer for function belonging to the Server class returning void and taking a string (input) and an int (fd)

		Rep									_rep;
		SocketIO							_io;
		std::vector<User>					_clients;
		std::vector<Channel>				_channels;
		char								_buffer[1024];
		int									_server_fd;
		int									_connected_clients;
		struct sockaddr_in					_address;
		socklen_t							_addrlen;
		const int							_port;
		const std::string					_password;
		std::map<std::string, cmdHandler>	_commands;

		void	initCommands();
		void	acceptClient();
		void	manageClient(int &index);

	public:
		Server(int port, std::string password);
		~Server();

		void	starting();
		void	run();
		void	commandHandler(std::string const &output, int const &current);
	
	private:
		void	joinCmd(std::vector<std::string> const &input, int fd, User &cUser);
		void	nickCmd(std::vector<std::string> const &input, int fd, User &cUser);
		void	passCmd(std::vector<std::string> const &input, int fd, User &cUser);
		void	userCmd(std::vector<std::string> const &input, int fd, User &cUser);
		void	msgCmd(std::vector<std::string> const &input, int fd, User &cUser);
		void	inviteCmd(std::vector<std::string> const &input, int fd, User &cUser);
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
