/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:56:45 by amann             #+#    #+#             */
/*   Updated: 2022/09/16 13:01:42 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	loop_to_first_column(t_list **options, t_window_info w)
{
	t_list	*current;
	int		prev_idx;

	prev_idx = g_state.cursor_idx;
	g_state.cursor_idx -= ((w.cols_to_display - 1) * w.col_height);
	if (g_state.cursor_idx < 0)
		g_state.cursor_idx += w.col_height;
	current = move_to_idx(*options, 0, g_state.cursor_idx);
	toggle_cursor(current);
	current = move_to_idx(current, g_state.cursor_idx, prev_idx);
	toggle_cursor(current);
}

void	move_cursor_right(t_list **options, t_window_info w)
{
	t_list	*current;

	if (g_state.cursor_idx + w.col_height < w.len)
	{
		current = move_to_idx(*options, 0, g_state.cursor_idx);
		toggle_cursor(current);
		current = move_to_idx(current, 0, w.col_height);
		toggle_cursor(current);
		g_state.cursor_idx += w.col_height;
	}
	else
		loop_to_first_column(options, w);
}
