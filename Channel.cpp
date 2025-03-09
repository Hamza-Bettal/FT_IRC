/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:09:47 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/08 04:00:06 by mohimi           ###   ########.fr       */
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

void Channel::addNewMember(Client user)
{
	this->members.push_back(user);
}

std::vector<Client>& Channel :: getMember()
{
	return (members);
}