/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:08:41 by zait-bel          #+#    #+#             */
/*   Updated: 2025/03/10 23:40:30 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <cstddef>
#include <vector>

void Server::invite(std::string data, Client user)
{
	for (size_t i = 0; i < __channels.size(); i++)
	{
		if (__channels[i].get_admin()->get_fd() == user.get_fd())
		{
			std::vector<std::string> 
		}
	}
}