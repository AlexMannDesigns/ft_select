/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:14:29 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 10:56:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	save_original_term_status(void)
{
	tcgetattr(STDIN_FILENO, &g_state.original_term);
}

static void	move_to_alt_screen(void)
{
	ft_putstr_fd(ALT_SCRN, g_state.fd);
}

static void	make_cursor_invisible(void)
{
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
}

static void	init_signal_handlers(void)
{
	signal(SIGWINCH, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGCONT, handle_signal);
	signal(SIGABRT, handle_signal);
	signal(SIGQUIT, handle_signal);
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
	init_signal_handlers();
	save_original_term_status();
	move_to_alt_screen();
	enable_raw_mode();
	make_cursor_invisible();
	setup_window();
}
