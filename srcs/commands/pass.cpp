/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:34:30 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/07 16:34:32 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::passCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
	if (input.size() > 1)
		cUser.setRPassword(input[1] == _password);
	else if (input.size() == 1)
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
	else if (cUser.getRegister() == true)
		_rep.E462(cUser.getFd(), cUser.getNick());
}
