/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:14:29 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 18:09:01 by amann            ###   ########.fr       */
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

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		restore_terminal();
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGWINCH)
		setup_window();
	else if (sig == SIGTSTP)
	{
		restore_terminal();
		signal(SIGTSTP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ioctl(g_state.fd, TIOCSTI, SUSPEND);
	}
	else if (sig == SIGCONT)
	{
		initialise_program();
	}
}

void	save_original_term_status(void)
{
	tcgetattr(STDIN_FILENO, &g_state.original_term);
}

void	move_to_alt_screen(void)
{
	ft_putstr_fd(ALT_SCRN, g_state.fd);
}

void	make_cursor_invisible(void)
{
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
}

void	initialise_program(void)
{
	char	*name;

	g_state.fd = open("/dev/tty", O_RDWR);
	g_state.cursor_idx = 0;
	name = getenv("TERM");
	if (!name)
	{
		ft_putstr_fd(NO_TERM, g_state.fd);
		exit(EXIT_FAILURE);
	}
	tgetent(NULL, name);
	save_original_term_status();
	move_to_alt_screen();
	enable_raw_mode();
	make_cursor_invisible();
	setup_window();
	signal(SIGWINCH, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGCONT, handle_signal);
}
