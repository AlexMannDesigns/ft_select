/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/28 18:48:17 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_state	g_state;

static int	process_keys(t_list **options, t_window_info w, char *buff)
{
	if (buff[0] == BACKSPACE || is_delete(buff))
		handle_delete(options);
	else if (buff[0] == ESC && buff[1] == ARROW)
		handle_scroll(options, w, buff);
	else if (buff[0] == SPACE)
		handle_select(options);
	else if (buff[0] == ENTER)
		return (1);
	else if (buff[0] == ESC)
	{
		restore_terminal();
		ft_lstdel(options, &delete_node);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int	control_loop(t_list **options)
{
	int					ret;
	int					exited;
	char				buff[read_buff_size];
	t_window_info		w;

	ft_bzero(buff, read_buff_size);
	while (*options)
	{
		if (g_state.window_change)
			print_options(options, &w);
		ret = read(g_state.fd, buff, read_buff_size);
		if (ret == -1)
			return (print_error(read_err, true));
		if (ret)
		{
			exited = process_keys(options, w, buff);
			if (exited)
				return (1);
			ft_bzero(buff, read_buff_size);
		}
	}
	return (0);
}

static int	process_keys(t_game *game, t_window_info w, char *buff)
{
	if (buff[0] == ESC && buff[1] == ARROW)
		handle_movement(game, w, buff);
	else if (buff[0] == ESC)
	{
		restore_terminal();
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static void	snake_control(void)
{
	int					ret;
	char				buff[read_buff_size];
	t_window_info		w;
	t_game				game;

	game.start = TRUE;
	ft_bzero(buff, read_buff_size);
	while (1)
	{
		//if (g_state.window_change)
		//	print_options(options, &w);
		update_game(&game, &w);
		ret = read(g_state.fd, buff, read_buff_size);
		if (ret == -1)
			return (print_error(read_err, true));
		if (ret)
		{
			process_snake_keys(&game, w, buff);
			ft_bzero(buff, read_buff_size);
		}
	}
	restore_terminal();
}

int	main(int argc, char **argv)
{
	t_list	*options;
	int		selected;
	int		init;

	if (argc == 1)
		display_usage();
	options = NULL;
	if (!initialise_options(&options, argv + 1) || !options)
	{
		print_error(MALLOC_ERR, FALSE);
		return (1);
	}
	init = initialise_program();
	if (init && ft_strequ(argv[1], "-snake"))
		snake_control();
	else if (init)
	{
		selected = control_loop(&options);
		restore_terminal();
		if (selected)
			print_select_result(options);
	}
	ft_lstdel(&options, &delete_node);
	return (0);
}
