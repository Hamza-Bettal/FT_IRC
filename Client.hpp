/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:53:53 by mohimi            #+#    #+#             */
/*   Updated: 2025/03/04 11:41:01 by mohimi           ###   ########.fr       */
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
    public:

        Client(const Client &src);
        Client &operator=(const Client &src);
        Client();
        Client(int fd, std::string ipadd);
        ~Client();
        //============ getters ============
        int            get_fd() const;
        std::string    get_IpAdd() const;

        //============ setters ============

        void        set_Fd(int fd);
        void        set_IpAdd(std::string ipadd);

}; 

#endif