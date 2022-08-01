/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:43:42 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 18:39:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/***** HEADER FILES *****/

# include "libft.h"
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
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
# define POSITION_CURSOR "\033[%d;%dH"
# define ALT_SCRN "\033[?1049h\033[H"
# define EXIT_ALT_SCRN "\033[?1049l"
# define UL_START "\033[4m"
# define UL_END "\033[24m"
# define REV_VIDEO "\033[7m"

/***** KEYBOARD MAPPING *****/

# define UP_ARROW 0x1b5b41
# define DOWN_ARROW 0x1b5b42
# define RIGHT_ARROW 0x1b5b43
# define LEFT_ARROW 0x1b5b44
# define ENTER_KEY 0xa
# define ESC_KEY 0x1b
# define DELETE_KEY 0x1b5b337e
# define BACKSPACE_KEY 0x08

/***** TERMCAP CODES *****/

# define CURSOR_INVISIBLE "vi"
# define CURSOR_NORMAL "ve"

/***** GLOBAL VARIABLES *****/

int	g_window_change;

/***** FUNCTION PROTOTYPES *****/

/* setup_window.c */
void	setup_window();

/* term_control_functions.c */
void	echo_off();
void	echo_canon_off();
int		my_putc(int c);
void	position_cursor(int y, int x);

#endif
