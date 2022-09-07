/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 12:20:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	restore_terminal()
{
	ft_putstr_fd(EXIT_ALT_SCRN, g_fd);
	tcsetattr(g_fd, TCSANOW, &g_original_term);
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
}
