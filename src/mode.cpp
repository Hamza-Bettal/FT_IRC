/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:32:42 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/14 11:33:27 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"
#include <cctype>
#include <cstddef>

bool isDigit(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void Server::mode(std::string data, Client user)
{
	std::vector<std::string> command = Server::split(data, ' ');
	
	if (command[1][0] == '#' || command[1][0] == '&')
	{	
		command[1] = command[1].substr(1, command[1].size());
		Channel *room = getChannel(command[1]);
		if (!room)
		{
			Server::send_msg(ERR_NOSUCHCHANNEL(command[1]), user.get_fd());
			return;
		}
		if (command.size() < 3 || command[2].size() < 3 || (command[2][0] != '+' && command[2][0] != '-'))
		{
			Server::send_msg(RPL_CHANNELMODEIS(user.get_nickName(), room->get_name(), "+/-", "i/t/k/o/l"), user.get_fd());
			return;
		}
		if (!room->isAdmine(user))
		{
			Server::send_msg(ERR_CHANOPRIVSNEEDED(room->get_name()), user.get_fd());
			return ;
		}
		if (command[2][0] == '+')
		{
			for (size_t i = 1; i < command.size(); i++)
			{
				if (command[2][i] == 'i')
					room->set_inviteMode(true);
				else if (command[2][i] == 't')
					room->set_topicMode(true);
				else if (command[2][i] == 'k' && command.size() > 3)
					room->set_key(command[3]);
				else if (command[2][i] == 'o' && command.size() > 3)
				{
					Client *member = getClient(command[3]);
					if (!member || !room->memberExist(*member))
					{
						Server::send_msg(ERR_USERNOTINCHANNEL(user.get_nickName(), room->get_name()), user.get_fd());
						continue ;
					}
					room->set_admin(*member);
				}
				else if (command[2][i] == 'l' && command.size() > 3 && isDigit(command[3]))
					room->set_limits(std::atol(command[3].c_str()));
			}
		}
		if (command[2][0] == '-')
		{
			for (size_t i = 1; i < command.size(); i++)
			{
				if (command[2][i] == 'i')
					room->set_inviteMode(false);
				else if (command[2][i] == 't')
					room->set_topicMode(false);
				else if (command[2][i] == 'k')
					room->set_key("");
				else if (command[2][i] == 'o' && command.size() > 3)
				{
					Client *member = getClient(command[3]);
					if (!member || !room->memberExist(*member))
					{
						Server::send_msg(ERR_USERNOTINCHANNEL(user.get_nickName(), room->get_name()), user.get_fd());
						continue ;
					}
					room->removeAdmin(*member);
				}
				else if (command[2][i] == 'l' && command.size() > 3 && isDigit(command[3]))
					room->set_limits(0);
			}
		}
	}
	// else
	// {
	// 	Client *member = getClient(command[1]);
	// 	if (!member)
	// 	{
	// 		Server::send_msg(ERR_NOSUCHNICK(command[1]), user.get_fd());
	// 		return;
	// 	}
	// 	if (member->get_nickName() != user.get_nickName())
	// 	{
	// 		Server::send_msg(ERR_USERDONOTMATCH(command[1]), user.get_fd());
	// 		return;
	// 	}
	// 	if (command.size() < 3)
	// 	{
	// 		Server::send_msg(RPL_CH(), user.get_fd());
	// 		return;
	// 	}
	// }
}
