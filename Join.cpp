
#include "Server.hpp"

void createChannel(std::string name, Client *user)
{
	Channel channel(name);
	
	channel.set_admin(user);
}

void check_key(std::string pass, Client *user, Channel *room, int fd)
{
	if (pass == room->get_key())
		room->addNewMember(*user);
	else
		Server::send_msg(ERR_INCORPASS(user->get_nickName()), fd);
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