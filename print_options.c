/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 12:07:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_options(t_list *options, size_t len)
{
	size_t			i;
	int				cols;
	int				rows;
	t_option_data	*data;

	if (len == 0 || !options)
		return ;
	get_cols_rows(&cols, &rows);
	ft_putstr_fd(CLEAR_SCRN, g_fd);
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		position_term_cursor((rows/2) - (len/2) + i, (cols - ft_strlen(data->name))/2);
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
