/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:42:49 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/05 21:19:31 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool setport(std::string str, int &port)
{
    std::stringstream ss(str);

    ss >> port;
    return ((ss.eof() && !ss.fail()) && !(port < 1024 || port > 65535));
}

bool checkpassowrd(std::string password)
{
	if (password.empty())
		return (0);
	for (int i = 0 ; i < static_cast<int>(password.size()); i++)
	{
		if (std::isspace(password[i]))
			return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	int			port = 5555;
	std::string	password;
	if (ac != 3 || !setport(av[1], port) || !checkpassowrd(av[2]))
	{
		std::cerr << "Error: invalid arg <port (1024 <->65535) password>" << std::endl;
		return (1);
	}
	Server s(port, av[2]);
	try
	{
		s.Server_Launcher();
        signal(SIGINT, Server::shutdown_sig);
        signal(SIGQUIT, Server::shutdown_sig);
	} catch (std::exception &e)
	{
        s.clearAll_Fds(s.get_Fdsocket());
		std::cout << e.what() << "\n";
		return (1);
	}
}