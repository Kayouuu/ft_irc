/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:00:00 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/03 11:47:54 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <iostream>
# include <vector>
# include <map>

# include <algorithm>
# include <ctime>
# include <csignal>
# include <cstring>
# include <cerrno>
# include <cstdlib>

# include "User.hpp"
# include "SocketIO.hpp"
# include "Channel.hpp"
# include "NumericReplies.hpp"

# define MAX_CONNECTIONS 1024
# define MAX_INCONNECTIONS 50
# define CYAN "\033[0;36m"
# define NO_COLOR "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

class	SocketIO;
class	Rep;
class	User;

class Server
{
	private:
		typedef	void (Server::*cmdHandler)(std::vector<std::string> &, User &); // Array of function pointer for function belonging to the Server class returning void and taking a string (input) and an int (fd)

		Rep									_rep;
		SocketIO							_io;
		std::vector<User>					_clients;
		std::vector<Channel>				_channels;
		int									_server_fd;
		int									_connected_clients;
		struct sockaddr_in					_address;
		const int							_port;
		const std::string					_password;
		std::map<std::string, cmdHandler>	_commands;
		std::string							_date;

		void	initCommands();
		void	acceptClient();
		void	manageClient(int &index);
		void	commandHandler(std::string const &output, int const &current);
		void	modeHandler(User &cUser, Channel &cChannel, char &mode, std::vector<std::string> &input, bool set);
		void	modeHandlerUser(int fd, std::string &input, User &cUser, char &mode);
		void	notAMode(std::string const &which, std::string const &input, User &cUser);

	public:
		Server(int port, std::string password);
		~Server();

		void		starting();
		void		run();
		void		shutdown();

	private:
		void	dieCmd(std::vector<std::string> &input, User &cUser);
		void	inviteCmd(std::vector<std::string> &input, User &cUser);
		void	joinCmd(std::vector<std::string> &input, User &cUser);
		void	kickCmd(std::vector<std::string> &input, User &cUser);
		void	modeCmd(std::vector<std::string> &input, User &cUser);
		void	msgCmd(std::vector<std::string> &input, User &cUser);
		void	nickCmd(std::vector<std::string> &input, User &cUser);
		void	noticeCmd(std::vector<std::string> &input, User &cUser);
		void	partCmd(std::vector<std::string> &input, User &cUser);
		void	passCmd(std::vector<std::string> &input, User &cUser);
		void	quitCmd(std::vector<std::string> &input, User &cUser);
		void	topicCmd(std::vector<std::string> &input, User &cUser);
		void	userCmd(std::vector<std::string> &input, User &cUser);
		void 	killCmd(std::vector<std::string> &input, User &cUser);
		void 	opCmd(std::vector<std::string> &input, User &cUser);

		// Channel modes
		void	bMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);
		void	iMode(Channel &cChannel, bool set);
		void	kMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);
		void	lMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);
		void	mMode(User &cUser, Channel &cChannel, bool set);
		void	nMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);
		void	oMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);
		void	tMode(Channel &cChannel, bool set);
		void	vMode(User &cUser, Channel &cChannel, std::string const &modeArg, bool set);

		// User mode
		void 	oMode(int fd, std::string &input, User &cUser);

		void    usrJoinChan(User &cUser, Channel &chan);

};

/*
Server algorithm:
1-Use of socket and bind, init sockaddr_in struct, listen in a "start" function
2-While loop
	a.Clear fdset and reinit all the clients in it 
	  (used by select to check all the clients that need to be checked)
	b.Use select() to listen for incoming events
	c.select will identify the fd that has events :
		-If it's the server fd, then we can accept a new client
		-If it's another fd(except -1 that will cause to break to loop
	    and exit the program), then we capp window  aspectn manage the client associated with the fd
	    and using recv to get what they send and eventually send them datas
	d.Looping
*/

#endif
