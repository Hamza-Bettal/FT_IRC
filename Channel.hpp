/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:06:32 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/10 01:47:49 by zait-bel         ###   ########.fr       */
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
        std::vector<Client>& getMember();

        void addNewMember(Client user);
};
#endif