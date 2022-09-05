/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:31:18 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 11:32:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

size_t	ft_list_len(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}