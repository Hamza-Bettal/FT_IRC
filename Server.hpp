/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:49:46 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/04 14:43:05 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <sstream>
#include <exception>
#include <cstring>

#include "Client.hpp"

#define color "\001\033[1;36m\002"
#define pos "\001\033[0;0m\002"
#define yellow "\001\033[1;33m\002"
#define grey "\001\033[1;30m\002"
#define lg "\001\033[92m\002"
#define b_italic "\001\033[1;3m\002"
#define gold "\001\033[38;5;220m\002" 
#define dark_blue "\001\033[34m\002"
#define teal "\001\033[38;5;30m\002"
#define violet "\001\033[38;5;128m\002"
#define b_ora "\001\033[1;38;5;208m\002"
#define RED "\x1b[31m"
#define ORANGE "\x1b[38;5;214m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"


class Server
{
    private :
        int                                __port;
        std::string                        __passWord;
        int                                __fd_socket;
        static   bool                      __signal;
        std::vector<struct pollfd>         __fDs;
        std::vector<Client>                __clients;
        Server(const Server &src);
        Server &operator=(const Server &src);
    public :
        Server(int port, std::string pass_word);
        void                            Server_Launcher();
        void                            ServerSocket();
        void                            addNew_Client();
        int                             get_Port();
        int                             get_Fdsocket();
        std::vector<Client>::iterator   get_client(int fd);
        void                            ReceiveNewData(int fd);
        void                            clearAll_Fds(int fd_client);
        static void                     shutdown_sig(int signal);
        ~Server();
}; 

#endif