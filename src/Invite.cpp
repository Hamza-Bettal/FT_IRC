/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:08:41 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/14 11:00:07 by hbettal          ###   ########.fr       */
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
	{
		Server::send_msg(ERR_NOSUCHNICK(command[1]), user.get_fd());
		return;
	}
	command[2] = command[2].substr(1, command[2].size());
	Channel *room = getChannel(command[2]);
	if (!room)
		Server::send_msg(ERR_NOSUCHCHANNEL(command[2]), user.get_fd());
	if (!room->memberExist(user))
	{
		Server::send_msg(ERR_NOTONCHANNEL(user.get_nickName(), command[2]), user.get_fd());
		return ;
	}
	if (room->getTopicMode() && !room->isAdmine(user))
	{
		Server::send_msg(ERR_CHANOPRIVSNEEDED(command[2]), user.get_fd());
		return ;
	}
	if (room->memberExist(*newMember))
	{
		Server::send_msg(ERR_USERONCHANNEL(command[2], command[1]), user.get_fd());
		return ;
	}
	if (room->getlimits() && room->getMembers().size() + 1 > room->getlimits())
	{
		Server::send_msg(ERR_CHANNELISFULL(user.get_nickName(), command[1]), user.get_fd());
		return ;
	}
	else
	{
		room->addNewMember(*newMember);
		Server::send_msg(RPL_INVITING(user.get_nickName(), newMember->get_nickName(), room->get_name()), user.get_fd());
		Server::send_msg(RPL_WELCOME(user.get_nickName(), "invited you to the channel"), newMember->get_fd());
		return ;
	}
}
