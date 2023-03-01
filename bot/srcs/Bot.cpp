/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/01 14:03:14 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Bot.hpp"

Bot::Bot(int const &port, std::string const &pass, std::string const &ip) : _port(port), _pass(pass), _ip(ip)
{
	_log_msg = "PASS " + pass + "\r\nNICK MysteryIc\r\nUSER MysteryIc 0 * :MysteryIc";
	_announce_msg = "---Bot conversation incoming---";
	_scoob_msg = "Ruh-roh--RAGGY!!!!";
	_shaggy_msg = "Zoinks Scoob!";
	_velma_msg = "Jinkies!";
	_daphne_msg = "Would you do it for a Scooby Snack?";
	_fred_msg = "Looks like we've got another mystery on our hands !";

	_isChan = false;
	_isConnected = false;
	_curr_time = std::time(NULL);
}

Bot::~Bot() { }


void	Bot::start()
{
	int	rvalue;

	_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socketFd < 0)
	{
		std::perror("socket");
		shutdown();
	}
	_saddr.sin_family = AF_INET;
	_saddr.sin_port = htons(_port);
	_local_host = gethostbyname(_ip.c_str());
	if (_local_host == NULL)
	{
		perror("gethostbyname");
		shutdown();
	}
	_saddr.sin_addr = *((struct in_addr *)_local_host->h_addr);

	rvalue = connect(_socketFd, (struct sockaddr *)&_saddr, sizeof(struct sockaddr_in));
	if (rvalue < 0)
	{
		perror("connect");
		shutdown();
	}
	fcntl(_socketFd, F_SETFL, O_NONBLOCK);
	emit(_log_msg, _socketFd);
	run();
}

void	Bot::shutdown()
{
	emit("QUIT IRCBot", _socketFd);
	std::exit(1);
}

void	Bot::run()
{
	int			rvalue;
	fd_set		read_fd_set;
	std::string	output;

	FD_ZERO(&read_fd_set); //  Cleaning the FD list before filling it
	FD_SET(_socketFd, &read_fd_set);
	rvalue = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
	if (rvalue < 0)
	{
		std::perror("select");
		throw std::exception();
	}
	receive(output, _socketFd);
	if (!output.find("001 MysteryIc") == 0)
	{
		std::cerr << "internal error: Couldn't connect to the irc server" << std::endl;
		shutdown();
	}
	output.clear();
	std::cout << "Bot connected to the server!" << std::endl;
	while (true)
	{
		rvalue = receive(output, _socketFd);
		if (output == "" && rvalue < 1)
		{
			std::cout << "error: connection lost" << std::endl;
			shutdown();
		}
		if (rvalue != 1)
			handle(output);
		if (_currChannel != "")
			check();
		output.clear();
	}
}

void	Bot::handle(std::string const &output)
{
	std::vector<std::string>	parsed_output;
	std::string					tmp;

	if (output.find(":MysteryIc JOIN ") != std::string::npos)
	{
		_currChannel = _possibleMsg;
		emit("PRIVMSG " + _currChannel + " :Bot will send messages here!", _socketFd);
	}
	for (size_t i = 0; i < output.length(); i++)
	{
		char c = output[i];
		if (std::isspace(c))
		{
			parsed_output.push_back(tmp);
			tmp.clear();
		}
		else
			tmp.push_back(c);
	}
	if (tmp != "")
		parsed_output.push_back(tmp);

	if (parsed_output[1] == "PRIVMSG")
		setMsg(parsed_output);
}
		
void	Bot::emit(std::string const &input, int const &fd) const
{
	std::string	msg = input + "\r\n";
	int 		error;

	error = send(fd, msg.c_str(), msg.size(), 0);
	if (error < 0)
	{
		std::perror("send");
		throw std::exception();
	}
}

int	Bot::receive(std::string &output, int const &fd)
{
	char	buffer[1024 + 1];
	int		rvalue;
	int		loop_exit; 

	while (1)
	{
		std::memset(&buffer, 1, 1024);
		rvalue = recv(fd, &buffer, 1024, 0);
		if (rvalue < 0)
		{
			if (errno == EAGAIN)
				return (1);
			std::perror("recv");
			throw std::exception();
		}
		if (buffer[rvalue] == 0 || rvalue == 0)
			break ;
		buffer[rvalue] = '\0';
		output.append(buffer);
		loop_exit = output.find(10);
		if (loop_exit >= 0 || loop_exit <= output.size())
			break ;
	}
	return (rvalue);
}

void	Bot::setMsg(std::vector<std::string> &input)
{
	std::string::const_iterator msg_it;
	std::string	user = input[0].substr(1, input[0].size());
	std::string	who = input[3];
	std::string	new_msg;

	std::vector<std::string>::iterator it = input.begin();
	it++; it++; it++; it++;

	while (it != input.end())
	{
		new_msg.append(*it);
		if (++it != input.end() && *it != "")
			new_msg.append(" ");
	}
	if (new_msg == "")
		who = ":HELP";
    for (msg_it = new_msg.begin(); msg_it != new_msg.end(); ++msg_it)
        if (!std::isspace(*msg_it))
			break ;

	if (msg_it == new_msg.end())
		who = "";
	if (who == ":SCOOBY" || who == ":SCOOB" || who == ":SCOOBY-DOO")
	{
		_scoob_msg = new_msg;
		emit("PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
	}
	else if (who == ":VELMA")
	{
		_velma_msg = new_msg;
		emit("PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
	}
	else if (who == ":SHAGGY")
	{
		_shaggy_msg = new_msg;
		emit("PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
	}
	else if (who == ":FRED")
	{
		_fred_msg = new_msg;
		emit("PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
	}
	else if (who == ":DAPHNE")
	{
		_daphne_msg = new_msg;
		emit("PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
	}
	else if (who == ":CHANNEL" && input[4] != "")
		setChannel(input[4]);
	else if (who == ":HELP")
		emit("PRIVMSG " + user + " Usage => /msg MysteryIc [SCOOBY, VELMA, SHAGGY, DAPHNE, FRED, CHANNEL] [message, #channelname] {...} {...}", _socketFd);
}

void	Bot::check()
{
	if (std::difftime(std::time(NULL), _curr_time) >= 300)
	{
		sendMsg();
		_curr_time = std::time(NULL);
	}
}

void	Bot::sendMsg()
{
	if (_currChannel == "")
		return ;
	std::cout << "Message sent!" << std::endl;
	emit("NOTICE " + _currChannel + " :" + _announce_msg, _socketFd);
	emit("PRIVMSG " + _currChannel + " SCOOBY-DOO: " + _scoob_msg, _socketFd);
	emit("PRIVMSG " + _currChannel + " VELMA: " + _velma_msg, _socketFd);
	emit("PRIVMSG " + _currChannel + " SHAGGY: " + _shaggy_msg, _socketFd);
	emit("PRIVMSG " + _currChannel + " DAPHNE: " + _daphne_msg, _socketFd);
	emit("PRIVMSG " + _currChannel + " FRED: " + _fred_msg, _socketFd);
}

void	Bot::setChannel(std::string const &chanName)
{
	emit("JOIN " + chanName, _socketFd);
	_possibleMsg = chanName;
}
