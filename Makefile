# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 18:48:59 by amann             #+#    #+#              #
#    Updated: 2022/09/16 12:29:52 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
FLAGS = -Wall -Wextra -Werror -ansi -std=c99 -pedantic -O3
SRCS = restore_terminal.c delete_node.c ft_list_len.c handle_delete.c			\
		handle_scroll.c handle_select.c helpers.c initialise_options.c			\
		initialise_program.c is_delete.c main.c move_to_idx.c					\
		move_cursor_left.c move_cursor_right.c print_options.c					\
		print_select_result.c setup_window.c term_control_functions.c			\
		enable_raw_mode.c toggle_cursor.c
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
