/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:53:53 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/05 22:09:53 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
 class Client
{
    private:
        int            __fDs;
        std::string    __ip_add;
        std::string    __nick_name;
        std::string    __user_name;
        bool           __has_pass;
        bool           __isRegistred;
        bool           __hasUser;
        bool           __hasNick;
    public:

        Client(const Client &src);
        Client &operator=(const Client &src);
        Client();
        Client(int fd, std::string ipadd, std::string nick, std::string user);
        ~Client();
        //============ getters ============
        int            get_fd() const;
        std::string    get_IpAdd() const;
        std::string    &get_userName();
        std::string    &get_nickName();
        bool           get_hasPass() const;
        bool           get_isRegistred() const;
        bool           get_hasUser() const;
        bool           get_hasNick() const;

        //============ setters ============

        void        set_Fd(int fd);
        void        set_IpAdd(std::string ipadd);
        void        set_userName(std::string user_name);
        void        set_nickName(std::string nick_name);
        void        set_hasPass(bool has_pass);
        void        set_isRegistred(bool is_registred);
        void        set_hasUser(bool has_user);
        void        set_hasNick(bool has_nick);

}; 

#endif