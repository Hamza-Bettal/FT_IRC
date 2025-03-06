/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/06 04:19:32 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <sstream>
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
void Channel :: set_key(std ::string key)
{
	this->key = key;
}
Client* Channel :: get_admin()
{
	return (admin);
}
void Channel :: set_admin(Client *user)
{
	admin = user;
}

void createChannel(std::string name, Client *user)
{
	Channel channel(name);
	
	channel.set_admin(user);
}

void Server::join(int fd, std::string data, Client *user)
{   
	std::vector<std::string> channel = Server::split(data, ' ');
	
	if (channel.size() < 2)
	{
		//err msg
	}
	std::string name = channel[1];
	if (name[0] != '#' || name[0] != '&')
	{
		//errmsg
	}
	name.substr(1, name.size() - 1);
	std::vector<Channel>::iterator it = __channels.begin();
	while(it != __channels.end())
	{
		if (it->get_name() == name)
			check_key(); // check if the key is correct
	}
	if (it == __channels.end())
		createChannel(name, user);
}