/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:50:32 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 15:06:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	print_winsize_message(char *msg)
{
	ft_putstr_fd(tgoto(tgetstr(CURSOR_MOVE, NULL), 0, 0), g_state.fd);
	ft_putstr_fd(CLEAR_SCRN_SET_YELLOW, g_state.fd);
	ft_putstr_fd(msg, g_state.fd);
}

static void	winsize_error_dispatch(t_window_info *w)
{
	if ((w->rows < 5 && w->cols < 10) || (w->cols < 18 && w->rows > 20))
		print_winsize_message(":(");
	else if (w->rows < 10 && w->cols < 20)
		print_winsize_message("halp");
	else if (w->rows < 20 && w->cols < 30)
		print_winsize_message("srsly?");
	else
		print_winsize_message("Make me bigger!!!");
}

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
	w->len = (int) ft_lst_len(options);
	if (w->len == 0)
		return (0);
	get_cols_rows(&(w->cols), &(w->rows));
	w->col_width = get_max_option_length(options) + PADDING;
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
		winsize_error_dispatch(w);
		return (0);
	}
	w->current_col = 1;
	return (1);
}
