/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:00:54 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 18:47:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	get_cols_rows(int *cols, int *rows)
{
	struct winsize	window;

	ioctl(1, TIOCGWINSZ, &window);
	*cols = window.ws_col;
	*rows = window.ws_row;
}

void	setup_window(void)
{
	char	*str = "HELLO";
	int		cols;
	int		rows;

	get_cols_rows(&cols, &rows);
	ft_putstr(CLEAR_SCRN);
	position_cursor(rows/2, (cols - strlen(str))/2);
	g_window_change = TRUE;
}
