/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:37:45 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 11:21:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	print_error(char *error_msg, int restore)
{
	if (restore)
		restore_terminal();
	ft_putstr_fd(error_msg, STDERR_FILENO);
	return (0);
}
