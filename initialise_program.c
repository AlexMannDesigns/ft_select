/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:14:29 by amann             #+#    #+#             */
/*   Updated: 2022/09/06 18:40:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 * solution for SIGTSTP found on stack overflow. We effectively reset the
 * terminal to its original settings, then reset the handling of that signal
 * to default and use ioctl effectively send ctrl-z to the terminal and send
 * ft_select to the background as normal. When the continue signal is received
 * we can then run initialise_program to display the ft_select interface.
 */

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
		return ;
	else if (sig == SIGWINCH)
		setup_window();
	else if (sig == SIGTSTP)
	{
		restore_terminal();
		signal(SIGTSTP, SIG_DFL);
		//nb kill and getpid are not permitted functions
		//kill(getpid(), SIGTSTP);
		ioctl(open("/dev/tty", O_RDWR), TIOCSTI, "\x1a");
	}
	else if (sig == SIGCONT)
	{
		initialise_program();
	}
}

void	initialise_program()
{
	char	*name;

	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(1, &g_original_term);
	tcgetattr(1, &g_current_term);
	g_current_term.c_cc[VMIN] = 0;
	g_current_term.c_cc[VTIME] = 1;
	tcsetattr(1, TCSANOW, &g_current_term);
	ft_putstr(ALT_SCRN);
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	signal(SIGWINCH, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGCONT, handle_signal);
}
