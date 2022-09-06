/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/06 17:29:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	restore_terminal()
{
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, &g_original_term);
	ft_putstr(EXIT_ALT_SCRN);
}
