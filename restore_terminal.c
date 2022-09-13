/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 13:44:00 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	restore_terminal()
{
	ft_putstr_fd(EXIT_ALT_SCRN, g_state.fd);
	tcsetattr(g_state.fd, TCSANOW, &g_state.original_term);
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
}
