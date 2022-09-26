/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:14:29 by amann             #+#    #+#             */
/*   Updated: 2022/09/26 11:23:16 by amann            ###   ########.fr       */
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

int	initialise_program(void)
{
	char	*name;

	g_state.fd = open("/dev/tty", O_RDWR);
	if (g_state.fd == -1)
		return (print_error(OPEN_ERR, FALSE));
	g_state.cursor_idx = 0;
	name = getenv("TERM");
	if (!name)
		return (print_error(NO_TERM, FALSE));
	tgetent(NULL, name);
	init_signal_handlers();
	save_original_term_status();
	move_to_alt_screen();
	if (!enable_raw_mode())
		return (print_error(TERMCAPS_ERR, TRUE));
	make_cursor_invisible();
	setup_window();
	return (1);
}
