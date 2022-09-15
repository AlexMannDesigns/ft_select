/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 11:35:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	process_keys(t_list **options, t_window_info w, char *buff)
{
	if (buff[0] == BACKSPACE || is_delete(buff))
		handle_delete(options);
	else if (buff[0] == ESC && buff[1] == ARROW)
		handle_scroll(options, w, buff);
	else if (buff[0] == SPACE)
		handle_select(options);
	else if (buff[0] == ENTER)
		return (0);
	else if (buff[0] == ESC)
		return (-1);
	return (1);
}

static int	control_loop(t_list **options)
{
	int					ret;
	int					exit;
	char				buff[BUFF_SIZE];
	t_window_info		w;

	ft_bzero(buff, BUFF_SIZE);
	ret = 0;
	while (1 && *options)
	{
		if (g_state.window_change)
			print_options(*options, &w);
		ret = read(g_state.fd, buff, BUFF_SIZE);
		if (ret)
		{
			if (ret == -1)
				handle_signal(SIGCONT);
			exit = process_keys(options, w, buff);
			if (exit == 0)
				return (0);
			if (exit == -1)
				return (-1);
			ft_bzero(buff, BUFF_SIZE);
		}
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_list			*options;
	int				exited;

	if (argc == 1)
		return (0);
	options = NULL;
	if (!initialise_options(&options, argv + 1) || !options)
		return (1);
	initialise_program();
	exited = control_loop(&options);
	restore_terminal();
	if (!exited)
		print_select_result(options);
	ft_lstdel(&options, &delete_node);
	return (0);
}
