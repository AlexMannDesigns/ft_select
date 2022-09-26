/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:21:55 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 14:30:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	delete_node(void *content, size_t content_size)
{
	t_option_data	*data;

	data = (t_option_data *) content;
	if (data)
	{
		ft_strdel(&(data->name));
		data->selected = 0;
		data->cursor = 0;
	}
	ft_memdel(&content);
	(void) content_size;
}
