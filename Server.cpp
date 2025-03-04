/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:23:33 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/04 16:04:56 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::__signal = false;

void Server::shutdown_sig(int signal)
{
    (void)signal;
    std::cout << "Server shutdown" << std::endl;
    __signal = true;
}

Server::Server(int port, std::string pass_word) : __port(port), __passWord(pass_word)
{
    __fd_socket = -1;
}

void Server::Server_Launcher()
{
    ServerSocket();
    while (!__signal)
        addNew_Client();
}

void Server::ServerSocket()
{
    int opt = 1;

    __fd_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (__fd_socket == -1)
        throw std::runtime_error("Error: socket failed");
    if (setsockopt(__fd_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("Error: setsockopt failed");
    if (fcntl(__fd_socket, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Error: fcntl failed");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(__port);//define port number assigned here
    if (bind(__fd_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Error: bind failed");
    if (listen(__fd_socket, 3) < 0)
        throw std::runtime_error("Error: listen failed");
    struct pollfd pfd;
    pfd.fd = __fd_socket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    __fDs.push_back(pfd);
}

void Server::addNew_Client()
{
    int new_socket;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    if (poll(__fDs.data(), __fDs.size(), -1) < 0)
        throw std::runtime_error("Error: poll failed");
    if (__fDs[0].revents & POLLIN)
    {
        if ((new_socket = accept(__fd_socket, (struct sockaddr *)&addr, (socklen_t *)&addrlen)) < 0)
            throw std::runtime_error("Error: accept failed");
        struct pollfd pfd;
        pfd.fd = new_socket;
        pfd.events = POLLIN;
        pfd.revents = 0;
        __fDs.push_back(pfd);

        __clients.push_back(Client());
        __clients.back().set_Fd(new_socket);
    }
    for (size_t i = 1; i < __fDs.size(); i++)
    {
        if (__fDs[i].revents & POLLIN)
            ReceiveNewData(__fDs[i].fd);
    }
}

void Server::ReceiveNewData(int fd)
{
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    size_t num_bytes = recv(fd, buff, sizeof(buff) - 1, 0);
    if (num_bytes <= 0)
    {
        std::cout << b_italic color "==>Client <" pos << fd << RED "> Disconnected" pos<< std::endl;
        clearAll_Fds(fd);
        close(fd);
    }
    else
    {
        buff[num_bytes] = '\0';
        std::cout << b_italic gold "==>Client <" pos << GREEN << fd << "> Data: " pos << buff;
    }
    
}

void Server::clearAll_Fds(int fd_client)
{
    close(fd_client);
    for (size_t i = 0; i < __fDs.size(); i++)
    {
        if(__fDs[i].fd == fd_client)
        {
            __fDs.erase(__fDs.begin() + i);
            break; 
        }
    }
}

Server::~Server()
{
    close(__fd_socket);
}

int Server::get_Port()
{
    return __port;
}

int Server::get_Fdsocket()
{
    return __fd_socket;
}

std::vector<Client>::iterator Server::get_client(int fd)
{
    for (std::vector<Client>::iterator it = __clients.begin(); it != __clients.end(); it++)
        if (it->get_fd() == fd)
            return it;
    return __clients.end();
}