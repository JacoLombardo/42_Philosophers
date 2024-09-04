# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:06:27 by jalombar          #+#    #+#              #
#    Updated: 2024/08/16 15:06:27 by jalombar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS = philo.c source/routine.c source/utils.c
HEADER = philo.h
NAME = philo

all: $(NAME)

$(NAME): $(SRCS) 
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
