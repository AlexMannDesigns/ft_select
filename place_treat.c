/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:04:13 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 13:04:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	place_treat(t_game *game, t_window_info w)
{
	srand(time(NULL));
	game->treat_x = (rand() % (w.cols - 2)) + 1;
	game->treat_y = (rand() % (w.rows - 2)) + 1;
}
