/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/03 16:05:02 by amann            ###   ########.fr       */
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

// remove options[cursor] from array by copying all other
// strings into a new array and freeing the original --> look into unsetenv function to handle this
// update the bits in selected by saving the bits beyond the deleted option to a temp
// then shifting them one to the right
// then set all bits to 0 from the selected bit to leftmost
// then set those bits to match the bits in the temp bit

size_t	handle_delete(size_t cursor, size_t *len, unsigned int *selected, char ***options)
{
	unsigned int temp;
	unsigned int mask;

	if (*selected || *len)
		;
	ft_remove_from_array(options, cursor);
	if (*selected & (1U << (cursor + 1)))
		cursor = handle_select(cursor, *len, selected) - 1;
	temp = *selected;
	mask = ~(~0 << (cursor + 1));
	*selected &= ~mask;
	temp &= mask;
	*selected >>= 1;
	*selected ^= temp;
	(*len)--;
	if (cursor >= *len)
		cursor = 0;
	g_window_change = TRUE;
	return (cursor);
}

static void	control_loop(char ***options)
{
	unsigned int		selected;
	int					ret;
	size_t				cursor;
	size_t				len;
	char				buff[10];

	len = ft_array_len(*options);
	selected = 0;
	cursor = 0;
	ft_bzero(buff, 10);
	ret = 0;
	while (1 && *options)
	{
		if (g_window_change)
			print_options(*options, cursor, len, selected);
		ret = read(1, buff, 10);
		if (ret)
		{
			if (buff[0] == BACKSPACE || (buff[0] == ESC && buff[1] == ARROW && buff[2] == 0x33 && buff[3] == 0x7e))
				cursor = handle_delete(cursor, &len, &selected, options);
			else if (buff[0] == ESC && buff[1] == ARROW)
				cursor = handle_scroll(cursor, len, buff);
			else if (buff[0] == SPACE)
				cursor = handle_select(cursor, len, &selected);
			else if (buff[0] == ESC) //must be last
				break ;
			ft_bzero(buff, 10);
		}
	}
}

void	print_bits(unsigned int nb)
{
	for (int i = 31 ; i >= 0 ; i--)
	{
		ft_printf("%c", ((nb & (1 << i)) ? '1' : '0'));
		if (i % 4 == 0)
			ft_printf(" ");
	}
	ft_putchar('\n');
}

void	print_select_result(char **options)
{
	unsigned int	i;

	i = 0;
	while (options[i])
	{
		ft_putstr(options[i]);
		if (options + i + 1)
			ft_putchar(' ');
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct termios	orig_term;
	struct termios	current_term;
	char			**options_array;


	if (argc == 1)
		return (0);
	options_array = ft_copy_array(argv + 1);
	if (!options_array)
		return (0);
	initialise_program(&orig_term, &current_term);
	control_loop(&options_array);
	close_program(&orig_term);
	print_select_result(options_array);
	return (0);
}
