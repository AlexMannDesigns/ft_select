/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:39:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 13:51:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// remove options[cursor] from array by copying all other
// strings into a new array and freeing the original --> look into unsetenv function to handle this
// update the bits in selected by saving the bits beyond the deleted option to a temp
// then shifting them one to the right
// then set all bits to 0 from the selected bit to leftmost
// then set those bits to match the bits in the temp bit

static void	close_program(struct termios *orig)
{
	tputs(tgetstr(CURSOR_NORMAL, NULL), 1, &my_putc);
	tcsetattr(1, TCSANOW, orig);
	ft_putstr(EXIT_ALT_SCRN);
}

/*
size_t	handle_delete(size_t cursor, size_t *len, unsigned int *selected, char ***options)
{
	unsigned int temp;
	unsigned int mask;

	if (*selected || *len)
		;
	ft_remove_from_array(options, cursor);
	if (*selected & (1U << (cursor + 1)))
		cursor = handle_select(cursor, *len, selected) - 1;
	temp = *selected;
	mask = ~(~0 << (cursor + 1));
	*selected &= ~mask;
	temp &= mask;
	*selected >>= 1;
	*selected ^= temp;
	(*len)--;
	if (cursor >= *len)
		cursor = 0;
	g_window_change = TRUE;
	return (cursor);
}

size_t	handle_select(size_t cursor, size_t len, unsigned int *selected)
{
	*selected ^= (1U << (cursor + 1));
	if (cursor == len - 1)
		cursor = 0;
	else
		cursor++;
	setup_window();
	return (cursor);
}

*/

/*
 * If we are dealing with a down arrow, we simply search through our list until
 * we find the node with cursor set to true. Set it to false and set the next
 * node's cursor value to true. If next == NULL, we set the node at the start
 * of the list to true.
 *
 * In the case of an up arrow, we search through the list inspecting the cursor
 * value of the NEXT node. We then set the current node's cursor to true and
 * next to false. If the cursor is on the first node, we set it to false and
 * cycle to the end of the list and set that to true.
 *
 * setup_window() sets our global variable to true so the changes take effect
 * on the next iteration.
 */

void	handle_scroll(t_list **options, char *buff)//, char **options)
{
	t_list			*current;
	t_option_data	*data;

	current = *options;
	if (buff[2] == DOWN_ARROW)
	{
		while (current)
		{
			data = (t_option_data *) current->content;
			if (data->cursor)
			{
				data->cursor = FALSE;
				if (current->next)
				{
					current = current->next;
					data = (t_option_data *) current->content;
					data->cursor = TRUE;
				}
				else
				{
					data = (t_option_data *) (*options)->content;
					data->cursor = TRUE;
				}
				break ;
			}
			current = current->next;
		}
	}
	else if (buff[2] == UP_ARROW)
	{
		;
	}
	setup_window();
}

static void	control_loop(t_list **options)
{
//	unsigned int		selected;
	int					ret;
//	size_t				cursor;
	size_t				len;
	char				buff[BUFF_SIZE];

//	selected = 0;
//	cursor = 0;
	ft_bzero(buff, BUFF_SIZE);
	ret = 0;
	while (1 && *options)
	{
		len = ft_list_len(*options);
		if (g_window_change)
			print_options(*options, len);
		ret = read(1, buff, BUFF_SIZE);
		if (ret)
		{
			//if (buff[0] == BACKSPACE || (buff[0] == ESC && buff[1] == ARROW && buff[2] == 0x33 && buff[3] == 0x7e))
			//	cursor = handle_delete(cursor, &len, options);
			if (buff[0] == ESC && buff[1] == ARROW)
				handle_scroll(options, buff);
			//else if (buff[0] == SPACE)
			//	cursor = handle_select(cursor, len, &selected);
			else if (buff[0] == ESC) //must be last
				break ;
			ft_bzero(buff, BUFF_SIZE);
		}
	}
}

/*
void	print_select_result(char **options)
{
	unsigned int	i;

	i = 0;
	while (options[i])
	{
		ft_putstr(options[i]);
		if (options + i + 1)
			ft_putchar(' ');
		i++;
	}
}
*/
int	main(int argc, char **argv)
{
	struct termios	orig_term;
	struct termios	current_term;
	t_list			*options;


	if (argc == 1)
		return (0);
	options = NULL;
	initialise_options(&options, argv + 1);
	if (!options)
		return (1);

	initialise_program(&orig_term, &current_term);
	control_loop(&options);
	close_program(&orig_term);
//	print_select_result(options_array);

	return (0);
}
