# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 15:29:57 by ssamadi           #+#    #+#              #
#    Updated: 2021/06/26 16:23:26 by ssamadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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