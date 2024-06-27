NAME      = lib.a
CC        = c++ -std=c++11
FLAGS     = -Wall -Wextra -Werror
RM        = rm -fr
AR		  = ar rc
OBJDIR    = .obj
FILES     = Poller/Poller KQueuer/KQueuer Epoller/Epoller Selector/Selector
SRC       = $(FILES:=.cpp)
OBJ       = $(addprefix $(OBJDIR)/, $(FILES:=.o))
INCLUEDES = Poller/Poller.hpp KQueuer/KQueuer.hpp Epoller/Epoller.hpp monitors.hpp IMonitor/IMonitor.hpp Selector/Selector.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

$(OBJDIR)/%.o: %.cpp $(INCLUEDES)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(OBJ)

fclean: clean
	$(RM)  $(NAME)

re: fclean all
.PHONY: all clean fclean re

