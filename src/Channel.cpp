/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/15 09:40:27 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/Server.hpp"
#include <cstddef>
#include <cstdio>
#include <vector>

Channel ::Channel() : name(""), invOnly(false), topicMode(false), limits(0){}
Channel ::Channel(std::string name) : name(name), invOnly(false), topicMode(false), limits(0){}

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
        Server::send_msg(RPL_WELCOME(user.get_nickName(), " has joind the channel"), members[i].get_fd());
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

void Channel::removeAdmin(Client user)
{
	std::vector<Client>::iterator it = admins.begin();
	while (it != admins.end())
	{
		if (user.get_fd() == it->get_fd())
		{
			this->admins.erase(it);
			return ;
		}
		it++;
	}
}

std::string Channel::nameReply()
{
	std::string reply;
	for (size_t i = 0; i < members.size(); i++)
	{
		reply += members[i].get_nickName();
		if (i + 1 < members.size())
			reply += ' ';
	}
	return reply;
}

size_t Channel::getlimits()
{
	return limits;
}

bool Channel::getInvOnlyMode()
{
	return invOnly;
}

bool Channel::getTopicMode()
{
	return topicMode;
}

void Channel::set_limits(size_t num)
{
	limits = num;
}

void Channel::set_inviteMode(bool mode)
{
	invOnly = mode;
}

void Channel::set_topicMode(bool mode)
{
	topicMode = mode;
}
