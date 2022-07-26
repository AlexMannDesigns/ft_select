/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:00:54 by amann             #+#    #+#             */
/*   Updated: 2022/09/14 17:23:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_cols_rows(int *cols, int *rows)
{
	struct winsize	window;

	ioctl(g_state.fd, TIOCGWINSZ, &window);
	*cols = window.ws_col;
	*rows = window.ws_row;
}

void	setup_window(void)
{
	g_state.window_change = TRUE;
}
