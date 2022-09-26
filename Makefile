# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 18:48:59 by amann             #+#    #+#              #
#    Updated: 2022/09/26 10:39:51 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
FLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O3
SRCS = delete_node.c display_usage.c enable_raw_mode.c get_window_info.c		\
		handle_delete.c	handle_scroll.c handle_select.c handle_signal.c			\
		initialise_options.c initialise_program.c is_delete.c main.c			\
		move_to_idx.c move_cursor_left.c move_cursor_right.c my_putc.c			\
		position_cursor_in_window.c print_select_result.c print_options.c		\
		print_error.c restore_terminal.c setup_window.c toggle_cursor.c
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
