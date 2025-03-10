/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/10 01:50:17 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Channel.hpp"
#include "Client.hpp"
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
Client* Channel :: get_admin()
{
	return (admin);
}

std::string Channel :: get_topic()
{
	return (topic);
}

std::vector<Client>& Channel :: getMember()
{
	return (members);
}

void Channel :: set_key(std ::string key)
{
	this->key = key;
}
void Channel :: set_admin(Client *user)
{
	admin = user;
}

void Channel::addNewMember(Client user)
{
	this->members.push_back(user);
}

void Channel::set_topic(std::string _topic)
{
	topic = _topic;
}