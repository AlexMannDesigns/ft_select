/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:11:21 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 18:33:14 by amann            ###   ########.fr       */
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
	t_option_data	*data;

	current = *options;
	while (current)
	{
		data = (t_option_data *) current->content;
		if (data->cursor)
		{
			data->cursor = FALSE;
			if (current->next)
			{
				current = current->next;
				data = (t_option_data *) current->content;
				data->cursor = TRUE;
			}
			else
			{
				data = (t_option_data *)(*options)->content;
				data->cursor = TRUE;
			}
			break ;
		}
		current = current->next;
	}
}

static void	move_cursor_to_end(t_option_data *data, t_list *current)
{
	data->cursor = FALSE;
	while (current->next)
		current = current->next;
	data = (t_option_data *) current->content;
	data->cursor = TRUE;
}

static void	move_cursor_up(t_list **options)
{
	t_list			*current;
	t_option_data	*data;

	current = *options;
	data = (t_option_data *) current->content;
	if (data->cursor)
		move_cursor_to_end(data, current);
	else
	{
		while (current->next)
		{
			data = (t_option_data *) current->next->content;
			if (data->cursor)
			{
				data->cursor = FALSE;
				data = (t_option_data *) current->content;
				data->cursor = TRUE;
				break ;
			}
			else
				current = current->next;
		}
	}
}

t_list	*move_to_next_column(t_list *current, t_window_info w)
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

t_list	*loop_to_first_column(t_list **options, t_window_info w, int i)
{
	t_list	*current;
	int		j;

	while (i - w.col_height >= 0)
		i -= w.col_height;
	j = 0;
	current = *options;
	while (j < i)
	{
		current = current->next;
		j++;
	}
	return (current);
}

void	move_cursor_right(t_list **options, t_window_info w)
{
	t_list			*current;
	t_option_data	*data;
	int				i;

	current = *options;
	i = 0;
	while (current)
	{
		data = (t_option_data *) current->content;
		if (data->cursor)
		{
			data->cursor = FALSE;
			if (i + w.col_height < w.len)
				current = move_to_next_column(current, w);
			else
				current = loop_to_first_column(options, w, i);
			data = (t_option_data *) current->content;
			data->cursor = TRUE;
			return ;
		}
		i++;
		current = current->next;
	}
}

t_list	*left_one_column(t_list **options, t_window_info w, int i)
{
	t_list	*current;
	int		j;

	current = *options;
	j = 0;
	while (j < i - w.col_height)
	{
		current = current->next;
		j++;
	}
	return (current);
}

t_list	*loop_to_end_column(t_list **options, t_window_info w, int i)
{
	t_list	*current;
	int		j;

	while (i + w.col_height < w.len)
		i += w.col_height;
	current = *options;
	j = 0;
	while (j < i && current->next)
	{
		current = current->next;
		j++;
	}
	return (current);
}

void	move_cursor_left(t_list **options, t_window_info w)
{
	t_list			*current;
	t_option_data	*data;
	int				i;

	current = *options;
	i = 0;
	while (current)
	{
		data = (t_option_data *) current->content;
		if (data->cursor)
		{
			data->cursor = FALSE;
			if (i - w.col_height >= 0)
				current = left_one_column(options, w, i);
			else
				current = loop_to_end_column(options, w, i);
			data = (t_option_data *) current->content;
			data->cursor = TRUE;
			return ;
		}
		i++;
		current = current->next;
	}
}

void	handle_scroll(t_list **options, t_window_info w, char *buff)
{
	if (buff[2] == DOWN_ARROW)
		move_cursor_down(options);
	else if (buff[2] == UP_ARROW)
		move_cursor_up(options);
	else if (buff[2] == RIGHT_ARROW)
		move_cursor_right(options, w);
	else if (buff[2] == LEFT_ARROW)
		move_cursor_left(options, w);
	setup_window();
}
