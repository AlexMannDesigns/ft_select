/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/06 15:52:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// remove options[cursor] from array by copying all other
// strings into a new array and freeing the original --> look into unsetenv function to handle this
// update the bits in selected by saving the bits beyond the deleted option to a temp
// then shifting them one to the right
// then set all bits to 0 from the selected bit to leftmost
// then set those bits to match the bits in the temp bit

static void	close_program(struct termios *orig)
{
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, orig);
	ft_putstr(EXIT_ALT_SCRN);
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
			if (buff[0] == BACKSPACE || (buff[0] == ESC && buff[1] == ARROW && buff[2] == 0x33 && buff[3] == 0x7e))
				handle_delete(options);
			else if (buff[0] == ESC && buff[1] == ARROW)
				handle_scroll(options, buff);
			else if (buff[0] == SPACE)
				handle_select(options);
			else if (buff[0] == ENTER)
				break ;
			else if (buff[0] == ESC) //must be last
			{
				ft_lstdel(options, &delete_node);
				break ; //close_program(&orig_term);
			}
			ft_bzero(buff, BUFF_SIZE);
		}
	}
}

void	print_select_result(t_list *options)
{
	t_option_data	*data;
	int				fd;
	int				first;

	first = TRUE;
	fd = open("/dev/tty", O_RDWR);
	while (options)
	{
		data = (t_option_data *) options->content;
		if (data->selected)
		{
			if (first)
				first = FALSE;
			else
				ft_putchar(' ');
			ft_putstr_fd(data->name, fd);
		}
		options = options->next;
	}
}

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
	print_select_result(options);
	ft_lstdel(&options, &delete_node);
	close_program(&orig_term);
	return (0);
}
