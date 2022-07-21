/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/07/21 18:57:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <stdio.h> //DELETE ME

void	get_cols_rows(int *cols, int *rows)
{
	struct winsize	window;

	ioctl(1, TIOCGWINSZ, &window);
	*cols = window.ws_col;
	*rows = window.ws_row;
}

void	move_cursor(int y, int x)
{
	printf(MOVE_CURSOR, y, x);
}

void	enter_alt_screen()
{
	printf("%s", ALT_SCRN);
}

void	exit_alt_screen()
{
	printf("%s", EXIT_ALT_SCRN);
}

void	echo_off()
{
	struct termios term;

	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void	canon_off()
{
	struct termios term;

	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void	underline_start()
{
	printf("\033[4m");
}

void	underline_end()
{
	printf("\033[24m");
}

void	reverse_video()
{
	printf("\033[7m");
}

void	setup_window()
{
	char	*str = "HELLO";
	int		cols;
	int		rows;

	get_cols_rows(&cols, &rows);
	printf("%s", CLEAR_SCRN);
	move_cursor(rows/2, (cols - strlen(str))/2);
	underline_start();
	printf("%s%s%s", YELLOW, BG_GREEN, str);
	underline_end();
	printf("\n\n");
	reverse_video();
	printf("HELLO AGAIN%s\n", RESET_COLOUR);
	printf(" \b\n");
}

int	main(int argc, char **argv)
{
	if (argc)
		;
	if (argv)
		;
//	int ret = tcgetattr(1, &termios_p);
//	termios_p.c_lflag &= ~(ICANON);
//	tcsetattr(1, TCSANOW, &termios_p);
//	char *name = getenv("TERM");
//	int i = tgetent(NULL, name);
//	printf("%s %d %d\n", name, i, ret);
	struct termios termios_p;
	char	c;

	c = 0;
	signal(SIGWINCH, &setup_window);
	enter_alt_screen();
	setup_window();
//	echo_off();
	while (1)
	{
		c = getchar();
		if (c == 'x')
			break ;
		else
		{
			printf("%x\n", c);
		}
	}
	exit_alt_screen();
	return (0);
}
