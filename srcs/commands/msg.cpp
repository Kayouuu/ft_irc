#include "../../incs/Server.hpp"

void Server::msgCmd(std::vector<std::string> input, int fd)
{
    std::vector<User>::iterator it = _clients.begin();
    while (fd != it->getFd())
        it++;
    if (it == _clients.end())
        ;//client pas trouver
}
