/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:54:18 by amann             #+#    #+#             */
/*   Updated: 2022/09/27 13:18:51 by amann            ###   ########.fr       */
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

static int	terminate_signal(int sig)
{
	if (sig == SIGINT || sig == SIGHUP || sig == SIGQUIT || sig == SIGILL
		|| sig == SIGTRAP || sig == SIGABRT || sig == SIGEMT || sig == SIGFPE
		|| sig == SIGBUS || sig == SIGSEGV || sig == SIGSYS || sig == SIGPIPE
		|| sig == SIGALRM || sig == SIGTERM || sig == SIGXCPU || sig == SIGXFSZ
		|| sig == SIGVTALRM || sig == SIGPROF || sig == SIGUSR1
		|| sig == SIGUSR2)
		return (1);
	return (0);
}

static int	stop_signal(int sig)
{
	if (sig == SIGTTIN || sig == SIGTTOU || sig == SIGTSTP)
		return (1);
	return (0);
}

void	handle_signal(int sig)
{
	if (terminate_signal(sig))
	{
		restore_terminal();
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGWINCH)
		setup_window();
	else if (stop_signal(sig))
	{
		restore_terminal();
		signal(SIGTSTP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ioctl(g_state.fd, TIOCSTI, SUSPEND);
	}
	else if (sig == SIGCONT)
		initialise_program();
}
