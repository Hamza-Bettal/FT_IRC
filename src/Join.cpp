/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:25:17 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/13 13:10:53 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"
#include <cstddef>
#include <vector>

void check_key(std::string pass, Client *user, Channel *room, int fd)
{
	if (pass == room->get_key())
    {
		room->addNewMember(*user);
        Channel::sendWelcomeMsg(*user, *room);
    }
	else
		Server::send_msg(ERR_INCORPASS(user->get_nickName()), fd);
}

void Server::leaveChannels(Client *user)
{
    for (size_t i = 0; i < this->__channels.size(); i++)
    {
        std::vector<Client>& members = __channels[i].getMembers();
        std::vector<Client>::iterator it = members.begin();
        while (it != members.end())
        {
            if (user->get_fd() == it->get_fd())
            {
                it = members.erase(it);
                break;
            }
            it++;
        }
    }
}


void Server::join(int fd, std::string data, Client *user) //FIXME:
{  
	std::vector<std::string> channel = Server::split(data, ' ');

	if (channel.size() < 2)
	{
		Server::send_msg((ERR_NEEDMOREPARAMS(data)), user->get_fd());
		return ;
	}
	std::vector<std::string> name = Server::split(channel[1], ',');
	std::string pass;
	if (channel.size() > 2)
		pass = Server::split(channel[2], ',')[0];
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i][0] == '0')
			this->leaveChannels(user);
		if (name[i][0] != '#' && name[i][0] != '&')
		{
			Server::send_msg(ERR_BADCHANMASK(name[i]), user->get_fd());
			return ;
		}
		name[i] = name[i].substr(1, name.size());
		size_t j;
		for (j = 0; j < __channels.size(); j++)
		{
			if (__channels[j].get_name() == name[i])
			{
				check_key(pass, user, &__channels[j], fd);
				break ;
			}
		}
		if (j == __channels.size())
		{
			Channel room(name[i]);
			room.set_admin(*user);
			room.addNewMember(*user);
			this->__channels.push_back(room);
			Channel::sendWelcomeMsg(*user, room);
		}
	}
}
