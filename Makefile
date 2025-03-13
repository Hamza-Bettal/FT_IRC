C++ = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
SRC = src/main.cpp src/Server.cpp src/Client.cpp src/Channel.cpp src/Join.cpp src/topic.cpp src/Invite.cpp src/kick.cpp src/privmsg.cpp
NAME = irc
OBJCS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJCS)
		$(C++) $(FLAGS) -o $(NAME) $(OBJCS)

%.o: %.cpp includes/Server.hpp includes/Client.hpp includes/Channel.hpp
	$(C++) $(FLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJCS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean