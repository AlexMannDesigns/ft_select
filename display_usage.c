/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:42:06 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 10:56:36 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_usage(void)
{
	ft_putstr_fd("Welcome to ft_select! Here's how to use it:\n",
		STDERR_FILENO);
	ft_putstr_fd("./ft_select argument1 [argument2...]\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
