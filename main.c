/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 18:44:00 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	interrupt()
{
	ft_putendl("HOW DARE YOU INTERRUPT ME");
}

void	print_options(char **options)
{
	int	i;

	i = 0;
	while (options[i])
	{
		ft_putstr(UL_START);
		ft_printf("%s%s%s{reset}", YELLOW, BG_GREEN, options[i]);
		ft_putstr(UL_END);
		if (options + i + 1)
			ft_putchar('\n');
		i++;
	}
	g_window_change = FALSE;
}

int	main(int argc, char **argv)
{
	if (argc)
		;
	if (argv)
		;
//	int ret = tcgetattr(1, &termios_p);
//	termios_p.c_lflag &= ~(ICANON);
//	tcsetattr(1, TCSANOW, &termios_p);
//	printf("%s %d %d\n", name, i, ret);
//	struct termios termios_p;
	char	c;
	struct termios	orig_term;
//	struct termios	current_term;

	char *name;

	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(1, &orig_term);

	c = 0;
	signal(SIGWINCH, &setup_window);
	signal(SIGINT, &interrupt);
	ft_putstr(ALT_SCRN);
	tputs(tgetstr(CURSOR_INVISIBLE, NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	while (1)
	{
		if (g_window_change)
			print_options(argv + 1);
		c = getchar();
		if (c == 'x' || c == ESC_KEY)
			break ;
	//	else
	//	{
	//		ft_printf("%x\n", c);
	//	}
	}
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, &orig_term);
	ft_putstr(EXIT_ALT_SCRN);
	return (0);
}
