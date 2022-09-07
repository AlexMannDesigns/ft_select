/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 12:30:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// remove options[cursor] from array by copying all other
// strings into a new array and freeing the original --> look into unsetenv function to handle this
// update the bits in selected by saving the bits beyond the deleted option to a temp
// then shifting them one to the right
// then set all bits to 0 from the selected bit to leftmost
// then set those bits to match the bits in the temp bit

void	print_select_result(t_list *options)
{
	t_option_data	*data;
//	int				fd;
	int				first;

	first = TRUE;
//	fd = open("test", O_RDWR);
	while (options)
	{
		data = (t_option_data *) options->content;
		if (data->selected)
		{
			if (first)
				first = FALSE;
			else
				ft_putstr(" ");
			ft_putstr(data->name);
		//	ft_putendl(data->name);
		}
		options = options->next;
	}
}

static int	control_loop(t_list **options)// struct termios *orig)
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
		ret = read(g_fd, buff, BUFF_SIZE);
		if (ret)
		{
			if (buff[0] == BACKSPACE || (buff[0] == ESC && buff[1] == ARROW && buff[2] == 0x33 && buff[3] == 0x7e))
				handle_delete(options);
			else if (buff[0] == ESC && buff[1] == ARROW)
				handle_scroll(options, buff);
			else if (buff[0] == SPACE)
				handle_select(options);
			else if (buff[0] == ENTER)
				return (0);
			else if (buff[0] == ESC) //must be last
				return (1); //restore_terminal(&orig_term);
			ft_bzero(buff, BUFF_SIZE);
		}
	}
	return (1);
}


int	main(int argc, char **argv)
{
	t_list			*options;
	int				exited;

	if (argc == 1)
		return (0);
	options = NULL;
	initialise_options(&options, argv + 1);
	if (!options)
		return (1);
	g_fd = open("/dev/tty", O_RDWR);
	initialise_program();
	exited = control_loop(&options);//, &orig_term);
	restore_terminal();
	if (!exited)
		print_select_result(options);
	ft_lstdel(&options, &delete_node);
	return (0);
}
