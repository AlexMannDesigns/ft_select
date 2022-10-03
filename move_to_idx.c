/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_idx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:25:25 by amann             #+#    #+#             */
/*   Updated: 2022/10/03 16:28:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_list	*move_to_idx(t_list *current, int from, int to)
{
	while (from != to && current)
	{
		(from)++;
		current = current->next;
	}
	return (current);
}
