/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:56:45 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 16:53:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_list	*move_to_next_column(t_list *current, t_window_info w)
{
	int	i;

	i = 0;
	while (i < w.col_height)
	{
		current = current->next;
		i++;
	}
	return (current);
}

static void	loop_to_first_column(t_list **options, t_window_info w)
{
	t_list	*current;
	int		prev_idx;
	int		i;

	prev_idx = g_state.cursor_idx;
	g_state.cursor_idx -= ((w.cols_to_display - 1) * w.col_height);
	if (g_state.cursor_idx < 0)
		g_state.cursor_idx += w.col_height;
	current = *options;
	i = 0;
	while (current)
	{
		if (i == g_state.cursor_idx)
			toggle_cursor(current);
		if (i == prev_idx)
		{
			toggle_cursor(current);
			break;
		}
		i++;
		current = current->next;
	}
}

void	move_cursor_right(t_list **options, t_window_info w)
{
	t_list	*current;
	int		i;

	current = *options;
	if (g_state.cursor_idx + w.col_height < w.len)
	{
		i = 0;
		while (current)
		{
			if (i == g_state.cursor_idx)
			{
				toggle_cursor(current);
				current = move_to_next_column(current, w);
				g_state.cursor_idx += w.col_height;
				toggle_cursor(current);
				break ;
			}
			i++;
			current = current->next;
		}
	}
	else
		loop_to_first_column(options, w);
}
