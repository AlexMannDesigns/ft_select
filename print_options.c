/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 13:13:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_options(t_list *options, size_t len)
{
	size_t			i;
	int				cols;
	int				rows;
	t_option_data	*data;

	get_cols_rows(&cols, &rows);
	ft_putstr(CLEAR_SCRN);
	i = 0;
	while (options)
	{
	//	ft_putendl("here");
		data = (t_option_data *) options->content;
		position_term_cursor((rows/2) - (len/2) + i, (cols - ft_strlen(data->name))/2);
		if (data->selected)
			ft_putstr(REV_VIDEO);
		if (data->cursor)
			ft_putstr(UL_START);
		ft_printf("%s%s{reset}", YELLOW, data->name);
		if (data->cursor)
			ft_putstr(UL_END);
		if (options->next)
			ft_putchar('\n');
		options = options->next;
		i++;
	}
	g_window_change = FALSE;
}
