C++ = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
SRC = main.cpp Server.cpp Client.cpp
NAME = irc
OBJCS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJCS)
		$(C++) $(FLAGS) -o $(NAME) $(OBJCS)

%.o: %.cpp Server.hpp Client.hpp Channel.hpp
	$(C++) $(FLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJCS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean