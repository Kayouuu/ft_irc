/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:34:30 by psaulnie          #+#    #+#             */
/*   Updated: 2023/02/13 10:20:36 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::passCmd(std::vector<std::string> &input, int fd, User &cUser)
{
	if (input.size() == 1)
		_rep.E461(cUser.getFd(), cUser.getNick(), input[0]);
	else if (input.size() > 1)
		cUser.setRPassword(input[1] == _password);
	else if (cUser.getRegister() == true)
		_rep.E462(cUser.getFd(), cUser.getNick());
}
