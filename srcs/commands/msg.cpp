/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:49:27 by dbouron           #+#    #+#             */
/*   Updated: 2023/02/08 13:49:27 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"

void Server::msgCmd(std::vector<std::string> const &input, int fd, User &cUser)
{
    std::vector<User>::iterator it = _clients.begin();
    while (fd != it->getFd())
        it++;
    if (it == _clients.end())
        ;//client pas trouver
}
