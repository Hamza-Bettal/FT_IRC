/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:42:49 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/08 03:13:05 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int ac, char **av)
{
	int			port;
	std::string	password;
	if (ac != 3 || !Server::setPort(av[1], port) || !Server::check_Passowrd(av[2]))
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
		std::cout << e.what() << std::endl;
		return (1);
	}
}