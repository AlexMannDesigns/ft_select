/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:28:51 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 15:37:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	free_and_exit(t_list **options, t_print_str p)
{
	print_error(MALLOC_ERR, TRUE);
	ft_lstdel(options, &delete_node);
	free(p.str);
	exit(EXIT_FAILURE);
}
