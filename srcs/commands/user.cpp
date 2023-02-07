/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:35:18 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/07 14:42:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

void	Server::userCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
	if (input.size() < 4)
		_rep.E461(fd, cUser.getNick(), input[0]);
	else if (cUser.getRegister() == true)
		_rep.E462(fd, cUser.getNick());
	else if (cUser.getRPassword() == true)
	{
		cUser.setUser(input[1]);
		// TODO set real name input[4]
		cUser.setRegister(true);
		_rep.R001(fd, cUser.getNick());
	}
}
