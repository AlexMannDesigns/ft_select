/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:02:23 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 16:04:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 * The process for selecting/highlighting options is nice and simple, we can
 * simply cycle through our list until we hit the cursor option, then toggle
 * the selected variable in that node.
 *
 * The project brief insistes that after highlighting, we shift the cursor
 * option to the next item. The original plan was to cal handle_scroll and
 * add a flag argument, but this felt messy, and it's fairly simple, so it's
 * implemented here.
 */

static void	scroll_to_next(t_option_data *data, t_list *cur, t_list **options)
{
	data->cursor = FALSE;
	if (cur->next)
		data = (t_option_data *) cur->next->content;
	else
		data = (t_option_data *) (*options)->content;
	data->cursor = TRUE;
}

void	handle_select(t_list **options)
{
	t_option_data	*data;
	t_list			*current;

	current = *options;
	while (current)
	{
		data = (t_option_data *) current->content;
		if (data->cursor)
		{
			if (data->selected)
				data->selected = FALSE;
			else
				data->selected = TRUE;
			scroll_to_next(data, current, options);
			break ;
		}
		current = current->next;
	}
	setup_window();
}
