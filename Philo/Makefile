# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 16:12:33 by fyardimc          #+#    #+#              #
#    Updated: 2022/08/28 16:39:00 by fyardimc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME_BONUS :=

NAME :=	philo

SRCS :=	 src_man/main.c src_man/philo_utils.c src_man/control_and_create.c src_man/handle_resources.c\
			src_man/time.c

OBJ := $(SRCS:%.c=%.o)

#SRCS_BONUS := 

#OBJ_BONUS := 

CC		 = @gcc
CFLAGS	 =  -I ./include -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "[\e[32mSUCCESS philosophers mandatory ready✅\e[0m]\n"

#$(NAME_BONUS): $(MAIN_BONUS) $(OBJ_BONUS)
#	@make -C ./printf
#	@make -C ./mlx
#	$(CC) $(CFLAGS) $(OBJ_BONUS) -framework OpenGL -framework AppKit mlx/libmlx.a ./printf/libftprintf.a $(MAIN_BONUS) -o $(NAME_BONUS) -ggdb
#	@printf "[\e[32mSUCCESS so_long bonus ready✅\e[0m]\n"

#bonus: $(NAME_BONUS)
	
clean:
	@rm -f src_man/*.o
	@printf "[\e[33mObject files are cleaned🚽\e[0m]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[\e[33mEverything cleaned🗑\e[0m ]\n"
re: fclean all

.PHONY: all clean fclean re bonus