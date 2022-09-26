/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:42:06 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 11:45:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_usage(void)
{
	print_error(WELCOME, FALSE);
	print_error(USAGE, FALSE);
	exit(EXIT_SUCCESS);
}
