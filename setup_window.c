/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:00:54 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 17:20:38 by amann            ###   ########.fr       */
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

void	setup_window()
{
	char	*str = "HELLO";
	int		cols;
	int		rows;

	get_cols_rows(&cols, &rows);
	ft_putstr(CLEAR_SCRN);
	position_cursor(rows/2, (cols - strlen(str))/2);
	ft_putstr(UL_START);
	ft_printf("%s%s%s", YELLOW, BG_GREEN, str);
	ft_putstr(UL_END);
	ft_putstr("\n\n");
	ft_putstr(REV_VIDEO);
	ft_printf("HELLO AGAIN%s\n", RESET_COLOUR);
	ft_putstr(" \b\n");
}
