/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_cursor_in_window.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:07:31 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 12:08:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*position_cursor_in_window(t_window_info *w, int i)
{
	int			x;
	int			y;

	if (w->len < w->rows)
		return (tgoto(tgetstr(CURSOR_MOVE, NULL), 0, i));
	if (i >= (w->current_col * w->col_height))
		(w->current_col)++;
	x = (w->current_col - 1) * w->col_width;
	if (i < w->col_height)
		y = i;
	else
		y = i - ((w->current_col - 1) * w->col_height);
	return (tgoto(tgetstr(CURSOR_MOVE, NULL), x, y));
}
