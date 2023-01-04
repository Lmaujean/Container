src      := main.cpp
inc      :=
obj      := $(src:%.cpp=%.o)
NAME     := Containers
CXX      := c++
CXXFLAGS := -I$(inc)
CFLAGS   := -std=c++98 -Wall -Wextra -Werror
.PHONY: all NAME
all: $(NAME)
$(NAME): $(obj)
	$(CXX) $^ $(LDFLAGS) -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@
.PHONY: clean fclean re
clean:
	$(RM) $(obj)
fclean: clean
	$(RM) $(NAME)
re: fclean all
