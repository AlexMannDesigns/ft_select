/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_snake.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:28 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 13:13:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_snake(t_game *game)
{
	size_t	i;
	char	*str;
	char	*temp;

	ft_putstr_fd("\x1B[2J", g_state.fd);
	str = tgoto(tgetstr(CURSOR_MOVE, NULL), game->treat_x, game->treat_y);
	ft_putstr_fd(str, g_state.fd);
	ft_putstr_fd("\033[41m  \033[0m", g_state.fd);
	ft_putstr_fd("\033[43m", g_state.fd);
	i = 0;
	while (i < game->len)
	{
		temp = tgetstr(CURSOR_MOVE, NULL);
		str = tgoto(temp, game->position[i][0], game->position[i][1]);
		ft_putstr_fd(str, g_state.fd);
		ft_putstr_fd("  ", g_state.fd);
		i++;
	}
	ft_putstr_fd("\033[0m", g_state.fd);
}
