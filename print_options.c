/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 18:37:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	get_max_option_length(t_list *options)
{
	int max;
	t_option_data *current;

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

void	position_cursor_in_window(t_window_info w, int i, int *current_col)
{
	int			x;
	int			y;

	if (w.cols_to_display >= w.len)
	{
		position_term_cursor(1, i * w.col_width);
		return ;
	}
	if (i >= (*current_col * w.col_height))
		(*current_col)++;
	x = (*current_col - 1) * w.col_width;
	if (i < w.col_height)
		y = i + 1;
	else
		y = i - ((*current_col - 1) * w.col_height) + 1;
	position_term_cursor(y, x);
}

int	get_window_info(t_window_info *w, t_list *options)
{
	w->len = (int) ft_list_len(options);
	if (w->len == 0)
		return (0);
	get_cols_rows(&(w->cols), &(w->rows));
	w->col_width = get_max_option_length(options) + 3;
	w->cols_to_display = (w->cols / w->col_width);
	if (w->cols_to_display == 0)
		w->cols_to_display = 1;
	w->col_height = (w->len / w->cols_to_display) + 1;
	if (w->col_height >= w->rows || w->col_width > w->cols)
	{
		position_term_cursor(1, 1);
		ft_putstr_fd("Make me bigger!!!", g_state.fd);
		return (0);
	}
	return (1);
}

void	print_options(t_list *options, t_window_info *w)
{
	int				i;
	int				current_col;
	t_option_data	*data;

	ft_putstr_fd(CLEAR_SCRN, g_state.fd);
	if (!get_window_info(w, options))
		return ;
	current_col = 1;
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		position_cursor_in_window(*w, i, &current_col);
		if (data->selected)
			ft_putstr_fd(REV_VIDEO, g_state.fd);
		if (data->cursor)
			ft_putstr_fd(UL_START, g_state.fd);
		ft_putstr_fd(YELLOW, g_state.fd);
		ft_putstr_fd(data->name, g_state.fd);
		ft_putstr_fd(RESET_COLOUR, g_state.fd);
		options = options->next;
		i++;
	}
	g_state.window_change = FALSE;
}
