/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_select_result.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:39:12 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 16:39:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_select_result(t_list *options)
{
	t_option_data	*data;
	int				first;

	first = TRUE;
	while (options)
	{
		data = (t_option_data *) options->content;
		if (data->selected)
		{
			if (first)
				first = FALSE;
			else
				ft_putstr(" ");
			ft_putstr(data->name);
		}
		options = options->next;
	}
}
