/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/11 22:19:53 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <vector>

Channel ::Channel(std::string name) : name(name){}

std::string Channel :: get_key()
{
	return (key);
}
std::string Channel :: get_name()
{
	return (name);
}
std::vector<Client> Channel :: get_admins()
{
	return (admins);
}

std::string Channel :: get_topic()
{
	return (topic);
}

std::vector<Client>& Channel::getMembers()
{
	return (members);
}

void Channel :: set_key(std ::string key)
{
	this->key = key;
}

void Channel :: set_admin(Client user)
{
	admins.push_back(user);
}

void Channel::set_topic(std::string _topic)
{
	topic = _topic;
}

void Channel::addNewMember(Client user)
{
	this->members.push_back(user);
}

bool Channel::memberExist(Client user)
{
	for (size_t i = 0; i < members.size(); i++)
	{
		if (user.get_fd() == members[i].get_fd())
			return true;
	}
	return false;
}

void Channel::sendWelcomeMsg(Client user, Channel room)
{
    std::vector<Client>& members = room.getMembers();
    for (size_t i = 0; i < members.size(); i++)
    {
        Server::send_msg(RPL_WELCOME(user.get_userName(), " has joind the channel"), members[i].get_fd());
    }
}

bool Channel::isAdmine(Client user)
{
	for (size_t i = 0; i < admins.size(); i++)
	{
		if (user.get_fd() == admins[i].get_fd())
			return true;
	}
	return false;
}

bool Channel::topicModeOn()
{
	return (topicMode);
}