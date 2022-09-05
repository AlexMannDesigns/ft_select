/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:11:21 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 16:01:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

void	handle_scroll(t_list **options, char *buff)
{
	if (buff[2] == DOWN_ARROW)
		move_cursor_down(options);
	else if (buff[2] == UP_ARROW)
		move_cursor_up(options);
	setup_window();
}
