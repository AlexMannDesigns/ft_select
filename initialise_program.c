/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:14:29 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 11:45:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	interrupt()
{
	return ;
}

void	initialise_program(struct termios *orig, struct termios *current)
{
	char	*name;

	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(1, orig);
	tcgetattr(1, current);
	current->c_cc[VMIN] = 0;
	current->c_cc[VTIME] = 1;
	tcsetattr(1, TCSANOW, current);
	ft_putstr(ALT_SCRN);
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	signal(SIGWINCH, &setup_window);
	signal(SIGINT, &interrupt);
}
