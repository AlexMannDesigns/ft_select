/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:53:46 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 17:57:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	loop_to_end_column(t_list **options, t_window_info w)
{
	t_list	*current;
	int		i;
	int		prev_idx;

	prev_idx = g_state.cursor_idx;
	g_state.cursor_idx += (w.col_height * (w.cols_to_display - 1));
	if (g_state.cursor_idx > w.len - 1)
		g_state.cursor_idx -= w.col_height;
	i = 0;
	current = *options;
	while (current)
	{
		if (i == prev_idx)
			toggle_cursor(current);
		else if (i == g_state.cursor_idx)
		{
			toggle_cursor(current);
			return ;
		}
		current = current->next;
		i++;
	}
}

void	move_cursor_left(t_list **options, t_window_info w)
{
	t_list			*current;
	int				i;

	current = *options;
	if (g_state.cursor_idx - w.col_height >= 0)
	{
		i = 0;
		while (current)
		{
			if (i == g_state.cursor_idx - w.col_height)
				toggle_cursor(current);
			if (i == g_state.cursor_idx)
			{
				toggle_cursor(current);
				g_state.cursor_idx -= w.col_height;
				return ;
			}
			i++;
			current = current->next;
		}
	}
	else
		loop_to_end_column(options, w);
}
