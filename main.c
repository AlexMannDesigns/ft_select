/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/07/22 13:55:00 by amann            ###   ########.fr       */
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

void	position_cursor(int y, int x)
{
	ft_printf(POSITION_CURSOR, y, x);
}

void	echo_off()
{
	struct termios term;

	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void	echo_canon_off()
{
	struct termios term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(1, TCSANOW, &term);
}

void	print_sequence(char *str)
{
	ft_putstr(str);
}

void	setup_window()
{
	char	*str = "HELLO";
	int		cols;
	int		rows;

	get_cols_rows(&cols, &rows);
	print_sequence(CLEAR_SCRN);
	position_cursor(rows/2, (cols - strlen(str))/2);
	print_sequence(UL_START);
	ft_printf("%s%s%s", YELLOW, BG_GREEN, str);
	print_sequence(UL_END);
	ft_putstr("\n\n");
	print_sequence(REV_VIDEO);
	ft_printf("HELLO AGAIN%s\n", RESET_COLOUR);
	ft_putstr(" \b\n");
}

int		my_putc(int c)
{
	write(1, &c, 1);
	return (c);
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
//	printf("%s %d %d\n", name, i, ret);
//	struct termios termios_p;
	char	c;
	struct termios	orig_term;
//	struct termios	current_term;

	char *name;

	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(1, &orig_term);

	c = 0;
	signal(SIGWINCH, &setup_window);
	print_sequence(ALT_SCRN);
	tputs(tgetstr("vi", NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	while (1)
	{
		c = getchar();
		if (c == 'x')
			break ;
	//	else
	//	{
	//		ft_printf("%x\n", c);
	//	}
	}
	print_sequence(tgetstr("ve", NULL));
	tcsetattr(1, TCSANOW, &orig_term);
	print_sequence(EXIT_ALT_SCRN);
	return (0);
}
