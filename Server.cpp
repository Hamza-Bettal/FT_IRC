/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:23:33 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/06 03:32:23 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

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
    addr.sin_port = htons(__port);
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

        Client c;
        c.set_Fd(new_socket);
        __clients.push_back(c);
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
    std::string data;
    Client *client = NULL;
    if (num_bytes <= 0)
    {
        std::cout << b_italic color "==>Client <" pos << fd << RED "> Disconnected" pos<< std::endl;
        clearAll_Fds(fd);
        close(fd);
    }
    else
    {
        for (size_t i = 0; i < __clients.size(); i++)
        {
            if (__clients[i].get_fd() == fd)
            {   
                client = &__clients[i];
                break;
            }
        }
        if (client == NULL)
            return ;
        data = buff;
        if (client->get_isRegistred())
            return ;
        if (data.find("USER") != std::string::npos)
            userName(fd, data);
        else if (data.find("NICK") != std::string::npos)
            nickName(fd, data);
        else if (data.find("PASS") != std::string::npos)
            passWord(fd, data);
        else if (data.find("JOIN") != std::string::npos)
            join(fd, data, client);
        if (!client->get_isRegistred() && client->get_hasPass() && client->get_hasNick() && client->get_hasUser())
        {
            client->set_isRegistred(true);
            send_msg(RPL_WELCOME(client->get_nickName().erase(client->get_nickName().find("\n")), "Welcome to the IRC server"), fd);
        }
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

void Server::userName(int fd, std::string data)
{
    std::string user = data.substr(5, data.size() - 5);
    std::string valid_user;
    std::string name;
    int count = 0;
    std::vector<std::string> sv = split(user, ' ');
    if (!sv.empty())
        valid_user = sv[0];
    for(std::vector<std::string>::iterator it = sv.begin(); it != sv.end(); it++)
        count++;
    std::vector<Client>::iterator it = get_client(fd);
    if (!it->get_hasPass()) 
    {
        send_msg(ERR_NOTREGISTERED, fd);
        return ;
    }
    if (count >= 4 || it != __clients.end())
    {
        it->set_userName(valid_user);
        it->set_hasUser(true);
    }
}

std::vector<Client>::iterator Server::client_nick(std::string nick_name)
{
    for (std::vector<Client>::iterator it = __clients.begin(); it != __clients.end(); it++)
        if (it->get_nickName() == nick_name)
            return it;
    return __clients.end();
}

void Server::nickName(int fd, std::string data)
{
    std::string nick = data.substr(5, data.size() - 5);
    std::vector<Client>::iterator it = get_client(fd);

    if (!it->get_hasPass()) 
    {
        send_msg(ERR_NOTREGISTERED, fd);
        return ;
    }
    if (it != __clients.end())
    {
        it->set_nickName(nick);
        it->set_hasNick(true);
    }
}

void Server::passWord(int fd, std::string data)
{
   std::string pass = data.substr(5, data.size() - 5);
   
    std::vector<Client>::iterator it = get_client(fd);
    if (pass.find("\r\n") != std::string::npos)
        pass = pass.erase(pass.find("\r\n"));
    else
        pass = pass.erase(pass.find("\n"));
   if (pass == __passWord)
        it->set_hasPass(true);
   else
   {
        send_msg(ERR_PASSWDMISMATCH(it->get_nickName()), fd);
        clearAll_Fds(fd);
        close(fd);
   }

}

std::vector<std::string> Server::split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

void Server::send_msg(std::string msg, int fd)
{
    send(fd, msg.c_str(), msg.size(), 0);
}