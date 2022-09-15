/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:45:21 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 16:45:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	toggle_cursor(t_list *current)
{
	t_option_data	*data;

	data = (t_option_data *) current->content;
	if (data->cursor)
		data->cursor = FALSE;
	else
		data->cursor = TRUE;
}
