/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/02 17:56:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

size_t	handle_select(size_t cursor, size_t len, unsigned int *selected)
{
	*selected ^= (1U << (cursor + 1));
	if (cursor == len - 1)
		cursor = 0;
	else
		cursor++;
	setup_window();
	return (cursor);
}


size_t	handle_scroll(size_t cursor, size_t len, char *buff)//, char **options)
{
	if (buff[2] == DOWN_ARROW)
	{
		cursor++;
		if (cursor > len - 1)
			cursor = 0;
	}
	else if (buff[2] == UP_ARROW)
	{
		if (cursor == 0)
			cursor = len - 1;
		else
			cursor--;
	}
	setup_window();
	return (cursor);
}

void	interrupt()
{
	return ;
}

static void	close_program(struct termios *orig)
{
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, orig);
	ft_putstr(EXIT_ALT_SCRN);
}

static void	initialise_program(struct termios *orig, struct termios *current)
{
	char	*name;

	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(1, orig);
	tcgetattr(1, current);
	current->c_cc[VMIN] = 0;
	current->c_cc[VTIME] = 1;
	tcsetattr(1, TCSANOW, current);
	ft_putstr(ALT_SCRN);
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	signal(SIGWINCH, &setup_window);
	signal(SIGINT, &interrupt);
}

void	print_options(char **options, size_t cursor, size_t len, unsigned int selected)
{
	size_t	i;
	int		cols;
	int		rows;

	get_cols_rows(&cols, &rows);
	ft_putstr(CLEAR_SCRN);
	i = 0;
	while (options[i])
	{
		position_term_cursor((rows/2) - (len/2) + i, (cols - ft_strlen(options[i]))/2);
		if (selected & (1U << (i + 1)))
			ft_putstr(REV_VIDEO);
		if (i == cursor)
			ft_putstr(UL_START);
		ft_printf("%s%s{reset}", YELLOW, options[i]);
		if (i == cursor)
			ft_putstr(UL_END);
		if (options + i + 1)
			ft_putchar('\n');
		i++;
	}
	g_window_change = FALSE;
}

static void	control_loop(char **options)
{
	unsigned int		selected;
	int					ret;
	size_t				cursor;
	size_t				len;
	char				buff[10];

	len = ft_array_len(options);
	selected = 0;
	cursor = 0;
	ft_bzero(buff, 10);
	ret = 0;
	while (1)
	{
		if (g_window_change)
			print_options(options, cursor, len, selected);
		ret = read(1, buff, 10);
		if (ret)
		{
			if (buff[0] == ESC_KEY && buff[1] == ARROW)
				cursor = handle_scroll(cursor, len, buff);
			else if (buff[0] == SPACE)
				cursor = handle_select(cursor, len, &selected);
			else if (buff[0] == ESC_KEY) //must be last
				break ;
			ft_bzero(buff, 10);
		}
	}
}

int	main(int argc, char **argv)
{
	struct termios	orig_term;
	struct termios	current_term;

	if (argc == 1)
		return (0);
	initialise_program(&orig_term, &current_term);
	control_loop(argv + 1);
	close_program(&orig_term);
	return (0);
}
