/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:40:03 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/23 08:50:13 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::quitCmd(std::vector<std::string> &input, User &cUser)
{
	close(cUser.getFd());
	cUser.setFd(-1);
	cUser.setNick("");
	cUser.setPrefix("");
	cUser.setUser("");
	cUser.setRegister(false);
	cUser.setRPassword(false);
	_connected_clients--;
}

//QUESTION: do we have to remove user from channels he's in ?
