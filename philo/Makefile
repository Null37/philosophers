# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 15:29:57 by ssamadi           #+#    #+#              #
#    Updated: 2021/07/04 17:30:06 by ssamadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

NAME = philo

FLAGS = -Wall -Wextra -Werror 

SRC = philo_main.c my_atoi.c philo_tools.c threads.c errors.c

CC = gcc

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC)  -o $(NAME)

clean: 
	@echo "no *.o" to clean

fclean: clean
	rm -f $(NAME)
	
re: fclean all