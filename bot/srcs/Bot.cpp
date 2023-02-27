/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:10:46 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/27 20:35:40 by psaulnie         ###   ########.fr       */
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
		return ;
	}
	
	_saddr.sin_family = AF_INET;
	_saddr.sin_port = htons(_port);
	_local_host = gethostbyname(_ip.c_str());
	if (_local_host == NULL)
	{
		perror("gethostbyname");
		return ;
	}
	_saddr.sin_addr = *((struct in_addr *)_local_host->h_addr);

	rvalue = connect(_socketFd, (struct sockaddr *)&_saddr, sizeof(struct sockaddr_in));
	if (rvalue < 0)
	{
		perror("connect");
		return ;
	}

	emit(_log_msg, _socketFd);
	
	run();
}

void	Bot::shutdown()
{
	
}

void	Bot::run()
{
	int			rvalue;
	std::string	output;

	receive(output, _socketFd);
	
	if (!output.find("001 MysteryIc") == 0)
	{
		std::cerr << "internal error: Couldn't connect to the irc server" << std::endl;
		return ;
	}
	output.clear();
	while (true)
	{
		receive(output, _socketFd);
		std::cout << output << std::endl;
		if (output.find(":MysteryIc JOIN ") != std::string::npos)
		{
			std::cout << "sal" << std::endl;
			_currChannel = _possibleMsg;
			emit(":MysteryIc PRIVMSG " + _currChannel + " Bot will send messages here!", _socketFd);
		}	// receive(output, _socketFd); // TODO only use one recv, put it in handle()
	// std::cout << ":MysteryIc JOIN " + chanName << std::endl;
	// std::cout << output.find(":MysteryIc JOIN " + chanName) << std::endl;
	// if (output.find(":MysteryIc JOIN " + chanName) != std::string::npos)
	// {
	// 	std::cout << "sal" << std::endl;
	// 	_currChannel = chanName;
	// 	emit(":MysteryIc PRIVMSG " + _currChannel + " Bot will send messages here!", _socketFd);
	// }
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

	std::cout << "Message sent: " << input << std::endl;
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
	std::string	user = input[0].substr(0, 1);
	std::string	who = input[3];
	std::string	new_msg;

	std::vector<std::string>::iterator it = input.begin();
	it++; it++; it++;

	while (it != input.end())
	{
		new_msg.append(*it);
		if (++it != input.end() && *it != "")
			new_msg.append(" ");
	}
	if (new_msg == "")
		who = "";
    for (msg_it = new_msg.begin(); msg_it != new_msg.end(); ++msg_it)
    {
        if (!std::isspace(*msg_it))
			break ;
    }
	if (msg_it == new_msg.end())
		who = "";
	if (who == ":SCOOBY" || who == ":SCOOB" || who == ":SCOOBY-DOO")
		_scoob_msg = new_msg;
	else if (who == ":VELMA")
		_velma_msg = new_msg;
	else if (who == ":SHAGGY")
		_shaggy_msg = new_msg;
	else if (who == ":FRED")
		_fred_msg = new_msg;
	else if (who == ":DAPHNE")
		_daphne_msg = new_msg;
	else if (who == ":CHANNEL" && input[4] != "")
	{
		setChannel(input[4]);
		return ;
	}
	else
	{
		emit(":MysteryIc PRIVMSG " + user + " Usage => /msg MysteryIc [SCOOBY, VELMA, SHAGGY, DAPHNE, FRED, CHANNEL] [message, #channelname] {...} {...}", _socketFd);
		return ;
	}
	emit(":MysteryIc PRIVMSG " + user + " " + who.substr(1, who.length() - 1) + " will now say: " + "\"" + new_msg + "\"", _socketFd);
}

void	Bot::check()
{
	if (std::difftime(std::time(NULL), _curr_time) >= 5)
	{
		sendMsg();
		_curr_time = std::time(NULL);
	}
}

void	Bot::sendMsg()
{
	if (_currChannel == "")
		return ;
	emit(":MysteryIc PRIVMSG " + _currChannel + " " + _announce_msg, _socketFd);
	emit(":SCOOBY-DOO PRIVMSG " + _currChannel + " " + _scoob_msg, _socketFd);
	emit(":VELMA PRIVMSG " + _currChannel + " " + _velma_msg, _socketFd);
	emit(":SHAGGY PRIVMSG " + _currChannel + " " + _shaggy_msg, _socketFd);
	emit(":DAPHNE PRIVMSG " + _currChannel + " " + _daphne_msg, _socketFd);
	emit(":FRED PRIVMSG " + _currChannel + " " + _fred_msg, _socketFd);
}

void	Bot::setChannel(std::string const &chanName)
{
	std::string	output;
	// TOCHECK for checking if a chan operator emit NAMES command
	emit("JOIN " + chanName, _socketFd);
	_possibleMsg = chanName;
	// receive(output, _socketFd); // TODO only use one recv, put it in handle()
	// std::cout << ":MysteryIc JOIN " + chanName << std::endl;
	// std::cout << output.find(":MysteryIc JOIN " + chanName) << std::endl;
	// if (output.find(":MysteryIc JOIN " + chanName) != std::string::npos)
	// {
	// 	std::cout << "sal" << std::endl;
	// 	_currChannel = chanName;
	// 	emit(":MysteryIc PRIVMSG " + _currChannel + " Bot will send messages here!", _socketFd);
	// }
	// emit JOIN with the channel
	// for (it = _channels.begin(); it != _channels.end(); it++)
	// {
	// 	std::cout << chanName << std::endl;
	// 	if (chanName == _currChannel)
	// 		break ;
	// }
	// if (it == _channels.end())
	// {
	// 	emit(":MysteryIc PRIVMSG " + _currChannel + " There is no such channel!", _socketFd);
	// 	return ;
	// }
}
