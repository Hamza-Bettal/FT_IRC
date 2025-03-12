/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:32:42 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/12 00:26:39 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"


void Server::mode(std::string data, Client user)
{
	std::vector<std::string> command = Server::split(data, ' ');
	
	if (command[2][0] == '#' || command[2][0] == '&')
	{	
		command[1].substr(1, command[1].size() - 1);
		Channel *room = getChannel(command[1]);
		if (!room)
		{
			Server::send_msg(ERR_NOSUCHCHANNEL(command[1]), user.get_fd());
			return;
		}
		if (command.size() < 3)
		{
			// Server::send_msg(RPL_UMODEIS(), user.get_fd());
			return;
		}
	}
	else
	{
		Client *member = getClient(command[1]);
		if (!member)
		{
			Server::send_msg(ERR_NOSUCHNICK(command[1]), user.get_fd());
			return;
		}
		if (member->get_nickName() != user.get_nickName())
		{
			Server::send_msg(ERR_USERDONOTMATCH(command[1]), user.get_fd());
			return;
		}
		if (command.size() < 3)
		{
			Server::send_msg(RPL_CH(), user.get_fd());
			return;
		}
	}
}