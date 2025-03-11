/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:06:32 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/11 04:22:49 by hbettal          ###   ########.fr       */
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
        Client                  *admin;
        std::vector<Client>     members;
        std::string             topic;

    public:

        Channel(std::string name);

        //getters
        std::string get_key();
        std::string get_name();
        Client		*get_admin();
		std::string	get_topic();

        //setters
        void set_key(std::string key);
		void set_topic(std::string topic);
        void set_admin(Client *user);
        std::vector<Client>& getMembers();

        void addNewMember(Client user);
        bool memberExist(Client user);
        static void sendWelcomeMsg(Client user, Channel room);
};
#endif