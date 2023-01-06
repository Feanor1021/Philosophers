NAME	= philo_bonus
CC	= @gcc
CFLAGS	= -Wall -Wextra -Werror -I ./include
SRCS	= $(wildcard src_bonus/*.c)
OBJS	= $(SRCS:.c=.o)

INCLUDE	= -pthread
FLAGS = -g -fsanitize=thread

HEADER	= philosophers_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS)
	@printf "[\e[32mSUCCESS philo bonus ready✅\e[0m]\n"
clean:
	@rm -f src_bonus/*.o
	@printf "[\e[33mObject files are cleaned🚽\e[0m]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[\e[33mEverything cleaned🗑\e[0m ]\n"

re: fclean all

.PHONY:	all clean fclean re
