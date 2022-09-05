/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 11:53:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// remove options[cursor] from array by copying all other
// strings into a new array and freeing the original --> look into unsetenv function to handle this
// update the bits in selected by saving the bits beyond the deleted option to a temp
// then shifting them one to the right
// then set all bits to 0 from the selected bit to leftmost
// then set those bits to match the bits in the temp bit
/*
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

*/

/*
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

*/
static void	close_program(struct termios *orig)
{
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, orig);
	ft_putstr(EXIT_ALT_SCRN);
}


void	print_options(t_list *options, size_t len)
{
	size_t			i;
	int				cols;
	int				rows;
	t_option_data	*data;

	get_cols_rows(&cols, &rows);
	ft_putstr(CLEAR_SCRN);
	i = 0;
	while (options)
	{
	//	ft_putendl("here");
		data = (t_option_data *) options->content;
		position_term_cursor((rows/2) - (len/2) + i, (cols - ft_strlen(data->name))/2);
		//if (selected & (1U << (i + 1)))
		//	ft_putstr(REV_VIDEO);
		if (data->cursor)
			ft_putstr(UL_START);
		ft_printf("%s%s{reset}", YELLOW, data->name);
		if (data->cursor)
			ft_putstr(UL_END);
		if (options->next)
			ft_putchar('\n');
		options = options->next;
		i++;
	}
	g_window_change = FALSE;
}

static void	control_loop(t_list **options)
{
//	unsigned int		selected;
	int					ret;
//	size_t				cursor;
	size_t				len;
	char				buff[BUFF_SIZE];

//	selected = 0;
//	cursor = 0;
	ft_bzero(buff, BUFF_SIZE);
	ret = 0;
	while (1 && *options)
	{
		len = ft_list_len(*options);
		if (g_window_change)
			print_options(*options, len);
		ret = read(1, buff, BUFF_SIZE);
		if (ret)
		{
			//if (buff[0] == BACKSPACE || (buff[0] == ESC && buff[1] == ARROW && buff[2] == 0x33 && buff[3] == 0x7e))
			//	cursor = handle_delete(cursor, &len, options);
		//	if (buff[0] == ESC && buff[1] == ARROW)
		//		cursor = handle_scroll(cursor, len, buff);
			//else if (buff[0] == SPACE)
			//	cursor = handle_select(cursor, len, &selected);
			if (buff[0] == ESC) //must be last
				break ;
			ft_bzero(buff, BUFF_SIZE);
		}
	}
}

/*
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
*/
int	main(int argc, char **argv)
{
	struct termios	orig_term;
	struct termios	current_term;
	t_list			*options;


	if (argc == 1)
		return (0);
	options = NULL;
	initialise_options(&options, argv + 1);
	if (!options)
		return (1);

	initialise_program(&orig_term, &current_term);
	control_loop(&options);
	close_program(&orig_term);
//	print_select_result(options_array);

	return (0);
}
