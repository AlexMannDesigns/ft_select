/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:28:51 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 15:29:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	free_and_exit(t_list **options)
{
	print_error(MALLOC_ERR, TRUE);
	ft_lstdel(options, &delete_node);
	exit(EXIT_FAILURE);
}
