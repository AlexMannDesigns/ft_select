/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 18:05:45 by amann            ###   ########.fr       */
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


static void	term_cursor_control(int rows, int cols, int len, int i, t_option_data *data, int display_cols, int max)
{
	int	x;
	int	y;
	int	col_len;
	int current_col;

	if (display_cols == 1)
	{
		y = (rows/2) - (len/2) + i + 1;
		x = (cols - data->len) / 2;
	}
	else
	{
		col_len = len / display_cols;
		current_col = 1;
		while (i > col_len * current_col)
			current_col++;
		//x = (current_col * (cols/display_cols)) - data->len/2 - (cols/display_cols/2);
		x = ((current_col - 1) * (max + 2)) + ((cols/2) - (max * (display_cols/2)));
		if (display_cols % 2 != 0)
		{
			x -= (max + 2) / 2;
		}
		if (i > col_len)
		{
			i = i - ((current_col - 1) * col_len) - 1;
		}
		y = (rows/2) - (col_len/2) + i + 1;
	}
	position_term_cursor(y, x);
}

static int	get_cols_to_display(int len, int cols, int rows, int max)
{
	int res;

	if (max > cols/2)
		return (1);
	if (len + 1 > rows)
	{
		res = 1;
		while (len + 1 > rows)
		{
			len = len / 2;
			res++;
		}
		return (res);
	}
	else
		return (1);
}

void	print_options(t_list *options, size_t len)
{
	size_t			i;
	int				cols;
	int				rows;
	int				cols_to_display;
	int				max;
	t_option_data	*data;

	if (len == 0 || !options)
		return ;

	get_cols_rows(&cols, &rows);
	max = get_max_option_length(options);
	cols_to_display = get_cols_to_display((int) len, cols, rows, max);
	ft_putstr_fd(CLEAR_SCRN, g_fd);
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;

		term_cursor_control(rows, cols, (int) len, (int) i, data, cols_to_display, max);

		if (data->selected)
			ft_putstr_fd(REV_VIDEO, g_fd);
		if (data->cursor)
			ft_putstr_fd(UL_START, g_fd);
		ft_putstr_fd(YELLOW, g_fd);
		ft_putstr_fd(data->name, g_fd);
		ft_putstr_fd(RESET_COLOUR, g_fd);
		if (data->cursor)
			ft_putstr_fd(UL_END, g_fd);
		if (options->next)
			ft_putchar_fd('\n', g_fd);
		options = options->next;
		i++;
	}
	g_window_change = FALSE;
}
