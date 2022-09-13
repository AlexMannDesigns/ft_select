/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:21:55 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 13:26:46 by amann            ###   ########.fr       */
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
	content_size = 0;
}
