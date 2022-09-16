/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:53:46 by amann             #+#    #+#             */
/*   Updated: 2022/09/16 13:01:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	loop_to_end_column(t_list **options, t_window_info w)
{
	t_list	*current;
	int		prev_idx;

	prev_idx = g_state.cursor_idx;
	g_state.cursor_idx += (w.col_height * (w.cols_to_display - 1));
	if (g_state.cursor_idx > w.len - 1)
		g_state.cursor_idx -= w.col_height;
	current = move_to_idx(*options, 0, prev_idx);
	toggle_cursor(current);
	current = move_to_idx(current, prev_idx, g_state.cursor_idx);
	toggle_cursor(current);
}

void	move_cursor_left(t_list **options, t_window_info w)
{
	t_list	*current;
	int		new_idx;

	if (g_state.cursor_idx - w.col_height >= 0)
	{
		new_idx = g_state.cursor_idx - w.col_height;
		current = move_to_idx(*options, 0, new_idx);
		toggle_cursor(current);
		current = move_to_idx(current, new_idx, g_state.cursor_idx);
		toggle_cursor(current);
		g_state.cursor_idx -= w.col_height;
	}
	else
		loop_to_end_column(options, w);
}
