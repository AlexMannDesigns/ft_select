# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:00:56 by amann             #+#    #+#              #
#    Updated: 2022/09/27 15:52:15 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c gnl_helpers.c
OBJ = get_next_line.o gnl_helpers.o

all:$(OBJ)
	@echo "\n\033[32mget_next_line compiled\033[0m\n"

%.o:%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
