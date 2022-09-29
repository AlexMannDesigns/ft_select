/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/29 15:59:28 by amann            ###   ########.fr       */
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
	char				buff[READ_BUFF_SIZE];
	t_window_info		w;

	ft_bzero(buff, READ_BUFF_SIZE);
	while (*options)
	{
		if (g_state.window_change)
			print_options(options, &w);
		ret = read(g_state.fd, buff, READ_BUFF_SIZE);
		if (ret == -1)
			return (print_error(READ_ERR, TRUE));
		if (ret)
		{
			exited = process_keys(options, w, buff);
			if (exited)
				return (1);
			ft_bzero(buff, READ_BUFF_SIZE);
		}
	}
	return (0);
}

static int	process_snake_keys(t_game *game, char *buff)
{
	if (buff[0] == ESC && buff[1] == ARROW)
	{
		if (buff[2] == RIGHT_ARROW && game->direction != LEFT_ARROW)
			game->direction = RIGHT_ARROW;
		else if (buff[2] == LEFT_ARROW && game->direction != RIGHT_ARROW)
			game->direction = LEFT_ARROW;
		else if (buff[2] == UP_ARROW && game->direction != DOWN_ARROW)
			game->direction = UP_ARROW;
		else if (buff[2] == DOWN_ARROW && game->direction != UP_ARROW)
			game->direction = DOWN_ARROW;
	}
	else if (buff[0] == ESC)
	{
		restore_terminal();
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	start_game(t_game *game, t_window_info *w)
{
	size_t	i;
	int		j;

	get_cols_rows(&(w->cols), &(w->rows));
	game->position = (int **) ft_memalloc(w->rows * w->cols * sizeof(int *));
	game->x = w->cols / 2;
	game->y = w->rows / 2;
	game->len = 20;
	i = 0;
	j = game->x;
	while (i < game->len)
	{
		game->position[i] = (int *) ft_memalloc(2 * sizeof(int));
		game->position[i][0] = j;
		game->position[i][1] = game->y;
		j--;
		i++;
	}
	game->direction = RIGHT_ARROW;
}

void	print_snake(t_game *game)
{
	size_t	i;

	//clear screen
	ft_putstr_fd("\x1B[2J", g_state.fd);
	//print treat
	ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), game->treat_x, game->treat_y), g_state.fd);
	ft_putstr_fd("\033[41m  \033[0m", g_state.fd);
	//set snake colour
	ft_putstr_fd("\033[43m", g_state.fd);
	//print array
	i = 0;
	while (i < game->len)
	{
		ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), game->position[i][0], game->position[i][1]), g_state.fd);
		ft_putstr_fd("  ", g_state.fd);
		i++;
	}
	//reset colour (for safety);
	ft_putstr_fd("\033[0m", g_state.fd);
}

void	place_treat(t_game *game, t_window_info w)
{
	srand(time(NULL));
	game->treat_x = (rand() % (w.cols - 1)) + 1;
	game->treat_y = (rand() % (w.rows - 1)) + 1;
}

int		draw_boundary(t_window_info w)
{
	if (w.cols < 40 || w.rows < 20)
	{
		//clear screen
		ft_putstr_fd("\x1B[2J", g_state.fd);
		ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), 1, 1), g_state.fd);
		ft_putstr_fd("Make me bigger", g_state.fd);
		g_state.window_change = FALSE;
		return (0);
	}
	if (w.cols > 60 || w.rows > 30)
	{
		//clear screen
		ft_putstr_fd("\x1B[2J", g_state.fd);
		ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), 1, 1), g_state.fd);
		ft_putstr_fd("Make me smaller", g_state.fd);
		g_state.window_change = FALSE;
		return (0);
	}
	return (1);
}

void	update_game(t_game *game, t_window_info w)
{
	size_t i;

	if (!draw_boundary(w))
		return ;
	if (game->direction == RIGHT_ARROW)
		game->x += 1;
	else if (game->direction == LEFT_ARROW)
		game->x -= 1;
	else if (game->direction == UP_ARROW)
		game->y -= 1;
	else if (game->direction == DOWN_ARROW)
		game->y += 1;
	//check boundary
	if (game->x == w.cols - 1 || game->x < 0 || game->y == w.rows || game->y < 0)
	{
		restore_terminal();
		exit(EXIT_SUCCESS);
	}
	//check collision with tail
	i = 0;
	while (i < game->len)
	{
		if (game->x == game->position[i][0] && game->y == game->position[i][1])
		{
			restore_terminal();
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	//check if treat has been eaten
	if ((game->x == game->treat_x || game->x == game->treat_x + 1 || game->x + 1 == game->treat_x)
			&& game->y == game->treat_y)
	{
		(game->len)++;
		game->position[game->len - 1] = ft_memalloc(sizeof(int) * 2);
		place_treat(game, w);
	}
	//move values of position array up by 1
	i = game->len - 1;
	while (i)
	{
		game->position[i][0] = game->position[i - 1][0];
		game->position[i][1] = game->position[i - 1][1];
		i--;
	}
	//set 0 idx of array to new x and y coords
	game->position[0][0] = game->x;
	game->position[0][1] = game->y;
	print_snake(game);
}

static void	snake_control(void)
{
	int					ret;
	char				buff[15];
	t_window_info		w;
	t_game				game;

	start_game(&game, &w);
	place_treat(&game, w);
	ft_bzero(buff, 15);
	while (1)
	{
		if (g_state.window_change)
			get_cols_rows(&(w.cols), &(w.rows));
		update_game(&game, w);
		ret = read(g_state.fd, buff, 15);
		if (ret == -1)
		{
			print_error(READ_ERR, TRUE);
			return ;
		}
		if (ret)
		{
			process_snake_keys(&game, buff);
			ft_bzero(buff, 15);
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
