/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/29 16:57:08 by amann            ###   ########.fr       */
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

void	exit_game(t_game *game)
{
	char	*arr[6];

	arr[0] = "What a great use of your time!";
	arr[1] = "Take a short break, you've earned it.";
	arr[2] = "A historic achievement";
	arr[3] = "Maybe you could add that to your CV";
	arr[4] = "wow";
	arr[5] = "Incredible";

	restore_terminal();
	srand(time(NULL));
	ft_printf("Your score: %d\n", game->score);
	ft_putendl(arr[rand() % 6]);
	exit(EXIT_SUCCESS);
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
		exit_game(game);
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
	game->len = 10;
	game->score = 0;
	i = 0;
	j = game->x;
	while (i < game->len)
	{
		game->position[i] = (int *) ft_memalloc(2 * sizeof(int));
		game->position[i][0] = j;
		game->position[i][1] = game->y;
		j -= 2;
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
	game->treat_x = (rand() % (w.cols - 2)) + 1;
	game->treat_y = (rand() % (w.rows - 2)) + 1;
}


static void	check_direction(t_game *game)
{
	if (game->direction == RIGHT_ARROW)
		game->x += 2;
	else if (game->direction == LEFT_ARROW)
		game->x -= 2;
	else if (game->direction == UP_ARROW)
		game->y -= 1;
	else if (game->direction == DOWN_ARROW)
		game->y += 1;
}

static void	check_game_over(t_game *game, t_window_info w)
{
	size_t	i;

	//check boundary
	if (game->x >= w.cols - 1 || game->x < 0 || game->y >= w.rows || game->y < 0)
		exit_game(game);
	//check collision with tail
	i = 0;
	while (i < game->len)
	{
		if (game->x == game->position[i][0] && game->y == game->position[i][1])
			exit_game(game);
		i++;
	}
}

static void	check_success(t_game *game, t_window_info w)
{
	//check if treat has been eaten
	if ((game->x == game->treat_x || game->x == game->treat_x + 1 || game->x + 1 == game->treat_x)
			&& game->y == game->treat_y)
	{
		(game->len)++;
		(game->score)++;
		game->position[game->len - 1] = ft_memalloc(sizeof(int) * 2);
		place_treat(game, w);
	}
}

static void	update_position(t_game *game)
{
	size_t	i;

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
}

void	update_game(t_game *game, t_window_info w)
{
	check_direction(game);
	check_game_over(game, w);
	check_success(game, w);
	update_position(game);
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
