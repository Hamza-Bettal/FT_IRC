/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:34:31 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/10 23:03:00 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		//TODO: err msg
		return ;
	}
	topic[1].substr(1, topic[1].size() - 1);
	for (size_t i = 0; i < __channels.size(); i++)
	{
		if (topic[1] == __channels[i].get_name())
		{
			if (topic.size() < 3)
				Server::send_msg(RPL_TOPIC(user->get_nickName(), topic[1], __channels[i].get_topic()), user->get_fd());
			else if (topic[2][0] == ':')
			{
				if (topic[2].size() == 1)
					__channels[i].set_topic("");
				else
					__channels[i].set_topic(topic[2].substr(2, topic[2].size() - 2));
			}
			// else
			// 	//TODO: err msg no ':'
		}
	}
}
