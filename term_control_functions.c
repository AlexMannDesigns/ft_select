/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_control_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:01 by amann             #+#    #+#             */
/*   Updated: 2022/08/02 17:09:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	position_term_cursor(int y, int x)
{
	ft_printf(POSITION_TERM_CURSOR, y, x);
}

void	echo_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void	echo_canon_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(1, TCSANOW, &term);
}

int	my_putc(int c)
{
	write(1, &c, 1);
	return (c);
}
