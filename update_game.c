/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:02:30 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 13:13:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

	if (game->x >= w.cols - 1 || game->x < 0
		|| game->y >= w.rows || game->y < 0)
		exit_game(game);
	i = 0;
	while (i < game->len)
	{
		if (game->x == game->position[i][0]
			&& game->y == game->position[i][1])
			exit_game(game);
		i++;
	}
}

static void	check_success(t_game *game, t_window_info w)
{
	if ((game->x == game->treat_x || game->x == game->treat_x + 1
			|| game->x + 1 == game->treat_x)
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

	i = game->len - 1;
	while (i)
	{
		game->position[i][0] = game->position[i - 1][0];
		game->position[i][1] = game->position[i - 1][1];
		i--;
	}
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
