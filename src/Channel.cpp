/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/13 13:10:53 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/Server.hpp"
#include <cstdio>
#include <vector>

Channel ::Channel() : name(""){}
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

void Channel::kickMember(Client user)
{
	std::vector<Client>::iterator it = members.begin();
	while (it != members.end())
	{
		if (user.get_fd() == it->get_fd())
		{
			this->members.erase(it);
			return ;
		}
		it++;
	}
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

void Channel::sendKickingMsg(Client sender, Channel room, Client target, std::string comment)
{
    std::vector<Client>& members = room.getMembers();
    for (size_t i = 0; i < members.size(); i++)
    {
		if (comment.empty())
        	Server::send_msg(RPL_KICKDEFMSG(sender.get_nickName(), room.get_name(), target.get_nickName()), members[i].get_fd());
		else
        	Server::send_msg(RPL_KICKMSG(sender.get_nickName(), room.get_name(), target.get_nickName(), comment), members[i].get_fd());
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