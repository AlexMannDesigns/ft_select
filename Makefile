# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 18:48:59 by amann             #+#    #+#              #
#    Updated: 2022/09/05 11:43:56 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
FLAGS = -Wall -Wextra -Werror -ansi -std=c99 -pedantic -O3 -g
SRCS = ft_list_len.c helpers.c initialise_options.c initialise_program.c main.c setup_window.c term_control_functions.c
OBJ = $(SRCS:%.c=%.o)
LIB_DIR = libft/
HEADER = -I includes/ -I $(LIB_DIR)includes
TERMCAPS = -ltermcap

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft -ltermcap

%.o:%.c
	gcc $(FLAGS) $(HEADER) -c $< -o $@

libft/libft.a:
	@echo compiling libft...
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo deleting object files...
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo deleting executable file\(s\)...
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

PHONY: all clean fclean re
