# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 15:29:57 by ssamadi           #+#    #+#              #
#    Updated: 2021/06/27 12:02:55 by ssamadi          ###   ########.fr        #
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

NAME = philoo

FLAGS = -g

SRC = philo/philo_main.c

CC = gcc

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC)  -o $(NAME)

clean: 
	@echo "no *.o" to clean

fclean: clean
	rm -f $(NAME)
	
re: fclean all