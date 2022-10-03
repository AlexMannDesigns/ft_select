/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:04:56 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 13:05:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

static void	start_game(t_game *game, t_window_info *w)
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

void	snake_control(void)
{
	int				ret;
	char			buff[15];
	t_window_info	w;
	t_game			game;

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
