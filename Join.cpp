#include "Channel.hpp"
#include "Server.hpp"
#include <cstddef>
#include <vector>

// void createChannel(std::string name, Client *user)
// {
// 	Channel channel(name);
	
// 	channel.set_admin(user);

// }

void sendWelcomeMsg (Client user, Channel room)
{

    std::vector<Client>& members = room.getMember();
    for (size_t i = 0; i < members.size(); i++)
    {
        Server::send_msg(RPL_WELCOME(user.get_userName(), " has joind the channel"), members[i].get_fd());
    }
}

void check_key(std::string pass, Client *user, Channel *room, int fd)
{
	if (pass == room->get_key())
    {
		room->addNewMember(*user);
        sendWelcomeMsg(*user, *room);
    }
	else
		Server::send_msg(ERR_INCORPASS(user->get_nickName()), fd);
}

void Server::leaveChannels(Client *user)
{
    for (size_t i = 0; i < this->__channels.size(); i++)
    {
        std::vector<Client>& members = __channels[i].getMember();
        std::vector<Client>::iterator it = members.begin();
        while (it != members.end())
        {
            if (user->get_fd() == it->get_fd())
            {
                it = members.erase(it);
                break;
            }
            it++;
        }
    }
}
void Server::topic(std::string data, Client *user)
{
	std::vector<std::string> topic = Server::split(data, ' ');
	if (topic.size() < 2)
	{
		Server::send_msg((ERR_NEEDMOREPARAMS(data)), user->get_fd());
		return ;
	}
	if (topic[1][0] != '#' && topic[1][0] != '&')
	{
		//TODO: err msg
		return ;
	}
	topic[1].substr(1, topic[1].size() - 1);
	for (size_t i = 0; i < __channels.size(); i++)
	{
		if (topic[1] == __channels[i].get_name())
		{
			if (topic.size() < 3)
				Server::send_msg(RPL_TOPIC(user->get_nickName(), topic[1], __channels[i].get_topic()), user->get_fd());
			else if (topic[2][0] == ':')
			{
				if (topic[2].size() == 1)
					__channels[i].set_topic("");
				else
					__channels[i].set_topic(topic[2].substr(1, topic[2].size() - 1));
			}
			// else
			// 	//TODO: err msg no ':'
		}
	}
}
void Server::join(int fd, std::string data, Client *user) //FIXME:
{  
	std::vector<std::string> channel = Server::split(data, ' ');
	
	if (channel.size() < 2)
	{
		//err msg
	}
	std::vector<std::string> name = Server::split(channel[1], ',');
	std::string pass;
	if (channel.size() > 2)
		pass = Server::split(channel[2], ',')[0];
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i][0] == '0')
			this->leaveChannels(user);
		if (name[i][0] != '#' || name[i][0] != '&')
		{
			//errmsg
		}
		name[i].substr(1, name.size() - 1);
		size_t j;
		bool found = false;
		for (j = 0; j < __channels.size(); j++)
		{
			if (__channels[j].get_name() == name[i])
			{
				found = true;
				check_key(pass, user, &__channels[j], fd);
			}
		}
		if (!found)
		{
			Channel room(name[i]);
			room.set_admin(user);
			room.addNewMember(*user);
			this->__channels.push_back(room);
			sendWelcomeMsg(*user, room);
		}
	}
}