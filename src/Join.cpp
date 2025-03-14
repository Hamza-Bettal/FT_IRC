/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:25:17 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/14 10:40:05 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"
#include <cstddef>
#include <vector>

void check_key(std::string pass, Client *user, Channel *room, int fd)
{
	if (room->memberExist(*user))
		return;
	if (pass == room->get_key())
    {
		room->addNewMember(*user);
        Channel::sendWelcomeMsg(*user, *room);
		Server::send_msg(RPL_TOPIC(user->get_nickName(), room->get_name(), room->get_topic()), user->get_fd());
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
	std::vector<std::string> command = Server::split(data, ' ');

	if (command.size() < 2 || command[1].size() < 3)
	{
		Server::send_msg((ERR_NEEDMOREPARAMS(data)), user->get_fd());
		return ;
	}
	std::vector<std::string> name = Server::split(command[1], ',');
	std::string pass;
	if (command.size() > 2)
		pass = Server::split(command[2], ',')[0];
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i][0] != '#' && name[i][0] != '&')
		{
			Server::send_msg(ERR_BADCHANMASK(name[i]), user->get_fd());
			return ;
		}
		name[i] = name[i].substr(1, name.size());
		if (name[i] == "0")
		{
			this->leaveChannels(user);
			continue ;
		}
		Channel *room = getChannel(name[i]);
		if (!room)
		{
			Channel room(name[i]);
			room.set_admin(*user);
			room.addNewMember(*user);
			this->__channels.push_back(room);
			Channel::sendWelcomeMsg(*user, room);
		}
		else
		{
			if (room->getInvOnlyMode())
			{
				Server::send_msg(ERR_INVITEONLYCHAN(user->get_nickName(), room->get_name()), user->get_fd());
				continue ;
			}
			if (room->getlimits() && room->getMembers().size() + 1 > room->getlimits())
			{
				Server::send_msg(ERR_CHANNELISFULL(user->get_nickName(), room->get_name()), user->get_fd());
				continue ;
			}
			check_key(pass, user, room, fd);
			break ;
		}
	}
}
