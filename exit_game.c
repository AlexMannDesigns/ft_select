/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:03:20 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 13:03:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
