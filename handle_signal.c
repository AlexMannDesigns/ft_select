/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:54:18 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 10:56:39 by amann            ###   ########.fr       */
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
