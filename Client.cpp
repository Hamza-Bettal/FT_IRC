/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:59:33 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/04 11:17:58 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
    __fDs = 0;
    __ip_add = "";
}

Client::~Client()
{
}

Client::Client(int fd, std::string ipadd)
{
    __fDs = fd;
    __ip_add = ipadd;
}

Client &Client::operator=(const Client &src)
{
    if (this != &src)
    {
        __fDs = src.__fDs;
        __ip_add = src.__ip_add;
    }
    return *this;
}

Client::Client(const Client &src)
{
    *this = src;
}
int            Client::get_fd() const
{
    return __fDs;
}

std::string    Client::get_IpAdd() const
{
    return __ip_add;
}

void        Client::set_Fd(int fd)
{
    __fDs = fd;
}

void        Client::set_IpAdd(std::string ipadd)
{
    __ip_add = ipadd;
}