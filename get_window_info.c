/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:50:32 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 11:57:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	get_max_option_length(t_list *options)
{
	int				max;
	t_option_data	*current;

	max = 0;
	while (options)
	{
		current = (t_option_data *) options->content;
		if ((int) current->len > max)
			max = current->len;
		options = options->next;
	}
	return (max);
}

int	get_window_info(t_window_info *w, t_list *options)
{
	g_state.window_change = FALSE;
	w->len = (int) ft_list_len(options);
	if (w->len == 0)
		return (0);
	get_cols_rows(&(w->cols), &(w->rows));
	w->col_width = get_max_option_length(options) + 3;
	w->cols_to_display = (w->cols / w->col_width);
	if (w->cols_to_display == 0)
		w->cols_to_display = 1;
	if (w->len < w->rows)
	{
		w->col_height = w->len;
		w->cols_to_display = 1;
	}
	else
		w->col_height = (w->len / w->cols_to_display) + 1;
	if (w->col_height >= w->rows || w->col_width > w->cols)
	{
		ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), 0, 0), g_state.fd);
		ft_putstr_fd(CLEAR_SCRN_SET_YELLOW, g_state.fd);
		ft_putstr_fd("Make me bigger!!!", g_state.fd);
		return (0);
	}
	w->current_col = 1;
	return (1);
}
