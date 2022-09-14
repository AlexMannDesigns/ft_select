/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:43:42 by amann             #+#    #+#             */
/*   Updated: 2022/09/14 16:14:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/***** HEADER FILES *****/

# include "libft.h"
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>

/***** COLOUR MACROS *****/

/* TEXT/FOREGROUND */
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET_COLOUR "\033[0m"

/* BACKGROUND */
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_PURPLE "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

/***** MISC BIT SEQUENCES *****/

# define CLEAR_SCRN "\x1B[2J"
# define POSITION_TERM_CURSOR "\033[%d;%dH"
# define ALT_SCRN "\033[?1049h\033[H"
# define EXIT_ALT_SCRN "\033[?1049l"
# define UL_START "\033[4m"
# define UL_END "\033[24m"
# define REV_VIDEO "\033[7m"
# define SUSPEND "\x1a"
# define RESET_DEFAULT_COLOUR "\033[0m\033[33m"
# define CLEAR_SCRN_SET_YELLOW "\x1B[2J\033[33m"
# define UL_REV_VIDEO_START "\033[4m\033[7m"

/***** KEYBOARD MAPPING *****/

# define ARROW 0x5b
# define UP_ARROW 0x41
# define DOWN_ARROW 0x42
# define RIGHT_ARROW 0x43
# define LEFT_ARROW 0x44
# define ENTER 0xa
# define SPACE 0x20
# define ESC 0x1b
# define BACKSPACE 0x7f
//# define DELETE 0x7f
//# define DELETE 0x1b5b337e

/***** TERMCAP CODES *****/

# define CURSOR_INVISIBLE "vi"
# define CURSOR_NORMAL "ve"

/***** MISC MACROS *****/

# define TRUE 1
# define FALSE 0
# define BUFF_SIZE 15

/***** STRUCTS *****/

typedef struct	s_state
{
	int				fd;
	int				window_change;
	struct termios	original_term;
	struct termios	current_term;
}					t_state;

typedef struct	s_option_data
{
	char	*name;
	size_t	len;
	int		selected;
	int		cursor;
}			t_option_data;

typedef struct	s_window_info
{
	int		cols;
	int		rows;
	int		len;
	int		col_width;
	int		col_height;
	int		cols_to_display;
}			t_window_info;

typedef struct s_print_str
{
	char	*str;
	size_t	len;
}			t_print_str;

/***** GLOBAL VARIABLES *****/

t_state	g_state;

/***** FUNCTION PROTOTYPES *****/

/* delete_node.c */
void	delete_node(void *content, size_t content_size);

/* enable_raw_mode.c */
void	enable_raw_mode(void);

/* ft_list_len.c */
size_t	ft_list_len(t_list *lst);

/* handle_delete.c */
void	handle_delete(t_list **options);

/* handle_scroll.c */
void	handle_scroll(t_list **options, t_window_info w, char *buff);

/* handle_select.c */
void	handle_select(t_list **options);

/* helpers.c */
char	**ft_copy_array(char **orig);
void	ft_remove_from_array(char ***orig, size_t idx);

/* initialise_options.c */
int		initialise_options(t_list **options, char **argv);

/* intialise_program.c */
void	initialise_program();

/* is_delete.c */
int		is_delete(char *buff);

/* print_options.c */
void	print_options(t_list *options, t_window_info *w);

/* print_select_result.c */
void	print_select_result(t_list *options);

/* restore_terminal.c */
void	restore_terminal(void);

/* setup_window.c */
void	setup_window();
void	get_cols_rows(int *cols, int *rows);

/* term_control_functions.c */
void	echo_off();
void	echo_canon_off();
int		my_putc(int c);
void	position_term_cursor(int y, int x);

#endif
