NAME = mutantStack

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -MD -std=c++98 -g3

BIN = bin/

INC = include

INCLUDE = $(addprefix -I , $(INC))

SRC =	main.cpp	\

OBJ := $(addprefix $(BIN), $(SRC:.cpp=.o))
DEPS =   $(OBJ:.o=.d)

all: $(BIN) $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(NAME) $(OBJ)

$(BIN)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)