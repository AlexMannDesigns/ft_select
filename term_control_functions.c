/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_control_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:01 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 13:45:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	position_term_cursor(int y, int x)
{
	char	*y_str;
	char	*x_str;

	y_str = ft_itoa(y);
	x_str = ft_itoa(x);
	if (!y_str || !x_str)
		return ;
	ft_putstr_fd("\033[", g_state.fd);
	ft_putstr_fd(y_str, g_state.fd);
	ft_putstr_fd(";", g_state.fd);
	ft_putstr_fd(x_str, g_state.fd);
	ft_putstr_fd("H", g_state.fd);
	free(y_str);
	free(x_str);
}

void	echo_off(void)
{
	struct termios	term;

	tcgetattr(g_state.fd, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(g_state.fd, TCSANOW, &term);
}

void	echo_canon_off(void)
{
	struct termios	term;

	tcgetattr(g_state.fd, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(g_state.fd, TCSANOW, &term);
}

int	my_putc(int c)
{
	write(g_state.fd, &c, 1);
	return (c);
}
