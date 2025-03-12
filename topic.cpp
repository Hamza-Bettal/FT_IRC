/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:34:31 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/11 23:00:13 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

void Server::topic(std::string data, Client *user)
{
	std::vector<std::string> topic = Server::split(data, ' ');
	if (topic.size() < 2)
	{
		Server::send_msg((ERR_NEEDMOREPARAMS(data)), user->get_fd());
		return ;
	}
	if (topic[1][0] != '#' && topic[1][0] != '&')
	{
		Server::send_msg(ERR_NOSUCHCHANNEL(topic[1]), user->get_fd());
		return ;
	}
	topic[1].substr(1, topic[1].size() - 1);

	Channel *room = getChannel(topic[1]);
	if (!room)
	{
		Server::send_msg(ERR_NOSUCHCHANNEL(topic[1]), user->get_fd());
		return;
	}

	if (!room->memberExist(*user))
	{
		Server::send_msg(ERR_NOTONCHANNEL(user->get_nickName(), topic[1]), user->get_fd());
		return ;
	}
	if (topic.size() < 3)
		Server::send_msg(RPL_TOPIC(user->get_nickName(), topic[1], room->get_topic()), user->get_fd());
	else if (topic[2][0] == ':')
	{
		if (topic[2].size() == 1)
			room->set_topic("");
		else
			room->set_topic(topic[2].substr(2, topic[2].size() - 2));
	}
}
