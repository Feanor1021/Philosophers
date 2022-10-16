
NAME	= philo
CC	= @gcc
CFLAGS	= -Wall -Wextra -Werror -I ./include
SRCS	= $(wildcard src_man/*.c)
OBJS	= $(SRCS:.c=.o)

INCLUDE	= -pthread
FLAGS = -g -fsanitize=thread

HEADER	= philosophers.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(CFLAGS) $(FLAGS) -o $(NAME) $(OBJS)
	@printf "[\e[32mSUCCESS philo mandatory ready✅\e[0m]\n"
clean:
	@rm -f src_man/*.o
	@printf "[\e[33mObject files are cleaned🚽\e[0m]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[\e[33mEverything cleaned🗑\e[0m ]\n"

re: fclean all

.PHONY:	all clean fclean remak
