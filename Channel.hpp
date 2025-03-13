/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:06:32 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/13 12:10:17 by hbettal          ###   ########.fr       */
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

        Channel( void );
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
        void        kickMember(Client user);
        bool		memberExist(Client user);
		bool		isAdmine(Client user);
        static void	sendWelcomeMsg(Client user, Channel room);
        static void sendKickingMsg(Client sender, Channel room, Client target, std::string comment);
};
#endif