/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:06:32 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/11 22:21:13 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <iostream>
#include <string>
#include <vector>


class Channel
{
    private:
        std::string             key;
        std::string             name;
        std::vector<Client>     admins;
        std::vector<Client>     members;
        std::string             topic;
		bool					topicMode;

    public:

        Channel(std::string name);

        //getters
        std::string				get_key();
        std::string				get_name();
        std::vector<Client>		get_admins();
		std::string				get_topic();
        std::vector<Client>&	getMembers();
		bool 					topicModeOn();

        //setters
        void	set_key(std::string key);
		void	set_topic(std::string topic);
        void	set_admin(Client user);
		void	set_topicMode(Client user);

        void		addNewMember(Client user);
        bool		memberExist(Client user);
		bool		isAdmine(Client user);
        static void	sendWelcomeMsg(Client user, Channel room);
};
#endif