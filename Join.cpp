
#include "Server.hpp"

void createChannel(std::string name, Client *user)
{
	Channel channel(name);
	
	channel.set_admin(user);
}

void sendWelcomeMsg (Client user, Channel room)
{

    std::vector<Client>& members = room.getMember();
    for (size_t i = 0; i < members.size(); i++)
    {
        std::string msg = user.get_userName() + " has joind the channel";
        Server::send_msg(msg, user.get_fd());
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

void Server::join(int fd, std::string data, Client *user)
{   
	std::vector<std::string> channel = Server::split(data, ' ');
	
	if (channel.size() < 2)
	{
		//err msg
	}
	std::string name = channel[1];
	std::string pass;
	if (channel.size() > 2)
		pass = channel[2];
    if (name[0] == '0')
        this->leaveChannels(user);
	if (name[0] != '#' || name[0] != '&')
	{
		//errmsg
	}
	name.substr(1, name.size() - 1);
	std::vector<Channel>::iterator it = __channels.begin();
	while(it != __channels.end())
	{
		if (it->get_name() == name)
		{
			check_key(pass, user, it.base(), fd); // check if the key is correct
		}
	}
	if (it == __channels.end())
		createChannel(name, user);
}