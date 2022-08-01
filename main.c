/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 17:20:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	interrupt()
{
	ft_putendl("HOW DARE YOU INTERRUPT ME");
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
	tputs(tgetstr("vi", NULL), 1, &my_putc);
	echo_canon_off();
	setup_window();
	while (1)
	{
		c = getchar();
		if (c == 'x')
			break ;
	//	else
	//	{
	//		ft_printf("%x\n", c);
	//	}
	}
	ft_putstr(tgetstr("ve", NULL));
	tcsetattr(1, TCSANOW, &orig_term);
	ft_putstr(EXIT_ALT_SCRN);
	return (0);
}
