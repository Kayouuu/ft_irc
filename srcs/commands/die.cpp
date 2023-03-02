/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:18:38 by psaulnie          #+#    #+#             */
/*   Updated: 2023/03/02 14:52:36 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void	Server::dieCmd(std::vector<std::string> &input, User &cUser)
{
	if (cUser.isIrcOp() == true)
		throw	std::exception();
	_rep.E481(cUser.getFd(), cUser.getNick());
}
