
NAME	= philo_bonus
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)

INCLUDE	= -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)
	@clear

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
