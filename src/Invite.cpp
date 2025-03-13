/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:08:41 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/13 13:10:53 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/Server.hpp"
#include <cstddef>
#include <vector>

void Server::invite(std::string data, Client user)
{
	std::vector<std::string> command = Server::split(data, ' ');

	if (command.size() < 3)
	{
		Server::send_msg(ERR_NEEDMOREPARAMS(data), user.get_fd());
		return ;
	}
	if (command[2][0] != '#' && command[2][0] != '&')
	{
		Server::send_msg(ERR_NOSUCHCHANNEL(command[2]), user.get_fd());
		return ;
	}
	Client *newMember = getClient(command[1]);
	if (!newMember)
		return;
	
	command[2] = command[2].substr(1, command[2].size());
	size_t i;
	for (i = 0; i < __channels.size(); i++)
	{
		if (__channels[i].get_name() == command[2])
		{
			if (!__channels[i].memberExist(user))
			{
				Server::send_msg(ERR_NOTONCHANNEL(user.get_nickName(), command[2]), user.get_fd());
				return ;
			}
			if (__channels[i].topicModeOn() && !__channels[i].isAdmine(user))
			{
				Server::send_msg(ERR_CHANOPRIVSNEEDED(command[2]), user.get_fd());
				return ;
			}
			if (!__channels[i].memberExist(*newMember))
			{
				__channels[i].addNewMember(*newMember);
				Channel::sendWelcomeMsg(*newMember, __channels[i]);
				return ;
			}
			else
			{
				Server::send_msg(ERR_USERONCHANNEL(command[2], command[1]), user.get_fd());
				return ;
			}
		}
	}
	if (i == __channels.size())
		Server::send_msg(ERR_NOSUCHCHANNEL(command[2]), user.get_fd());
}
