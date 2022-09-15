/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:11:21 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 17:18:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 * If we are dealing with a down arrow, we simply search through our list until
 * we find the node with cursor set to true. Set it to false and set the next
 * node's cursor value to true. If next == NULL, we set the node at the start
 * of the list to true.
 *
 * In the case of an up arrow, we search through the list inspecting the cursor
 * value of the NEXT node. We then set the current node's cursor to true and
 * next to false. If the cursor is on the first node, we set it to false and
 * cycle to the end of the list and set that to true.
 *
 * setup_window() sets our global variable to true so the changes take effect
 * on the next iteration.
 */

static void	move_cursor_down(t_list **options)
{
	t_list			*current;
	int				i;

	i = 0;
	current = *options;
	while (current)
	{
		if (i == g_state.cursor_idx)
		{
			toggle_cursor(current);
			if (current->next)
			{
				current = current->next;
				toggle_cursor(current);
				g_state.cursor_idx++;
			}
			else
			{
				toggle_cursor(*options);
				g_state.cursor_idx = 0;
			}
			break ;
		}
		current = current->next;
		i++;
	}
}

static void	move_cursor_to_end(t_option_data *data, t_list *current)
{
	int	i;

	i = 0;
	data->cursor = FALSE;
	while (current->next)
	{
		current = current->next;
		i++;
	}
	toggle_cursor(current);
	g_state.cursor_idx = i;
}

static void	move_cursor_up(t_list **options)
{
	t_list			*current;
	t_option_data	*data;
	int				i;

	current = *options;
	data = (t_option_data *) current->content;
	if (data->cursor)
		move_cursor_to_end(data, current);
	else
	{
		i = 0;
		while (current->next)
		{
			if (i == g_state.cursor_idx - 1)
			{
				toggle_cursor(current->next);
				toggle_cursor(current);
				g_state.cursor_idx--;
				break ;
			}
			current = current->next;
			i++;
		}
	}
}

void	handle_scroll(t_list **options, t_window_info w, char *buff)
{
	if (buff[2] == DOWN_ARROW)
	{
		move_cursor_down(options);
		setup_window();
	}
	else if (buff[2] == UP_ARROW)
	{
		move_cursor_up(options);
		setup_window();
	}
	else if (w.cols_to_display > 1)
	{
		if (buff[2] == RIGHT_ARROW)
			move_cursor_right(options, w);
		else if (buff[2] == LEFT_ARROW)
			move_cursor_left(options, w);
		setup_window();
	}
}
