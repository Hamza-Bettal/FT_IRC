/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:08:41 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/11 04:24:43 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <cstddef>
#include <vector>

void Server::invite(std::string data, Client user)
{
	std::vector<std::string> command = Server::split(data, ' ');

	if (command.size() != 3)
	{
		//TODO: err msg that the number of argements is wrong
		return ;
	}
	if (command[2][0] != '#' && command[2][0] != '&')
	{
		//channel name should start with # or &
		return ;
	}
	Client newMember;
	size_t i;
	for (i = 0; i < __clients.size(); i++)
	{
		if (__clients[i].get_nickName() == command[1])
		{
			newMember = __clients[i];
			break ;
		}
	}
	command[2].substr(1, command[2].size() - 1);
	for (i = 0; i < __channels.size(); i++)
	{
		if (__channels[i].get_name() == command[2])
		{
			if (__channels[i].get_admin()->get_fd() == user.get_fd())
			{
				if (!__channels[i].memberExist(newMember))
				{
					__channels[i].addNewMember(newMember);
					Channel::sendWelcomeMsg(newMember, __channels[i]);
					return ;
				}
				else
				{
					//TODO: err msg the member is already in the channel
				}
			}
		}
	}
	if (i == __channels.size())
	{
		//TODO: err msg channel not found
	}
}
