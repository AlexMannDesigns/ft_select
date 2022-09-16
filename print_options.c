/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/16 20:08:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	*position_cursor_in_window(t_window_info w, int i, int *current_col)
{
	int			x;
	int			y;

	if (w.len < w.rows)
		return (tgoto(tgetstr(CURSOR_MOVE, NULL), 0, i));
	if (i >= (*current_col * w.col_height))
		(*current_col)++;
	x = (*current_col - 1) * w.col_width;
	if (i < w.col_height)
		y = i;
	else
		y = i - ((*current_col - 1) * w.col_height);
	return (tgoto(tgetstr(CURSOR_MOVE, NULL), x, y));
}

static int	print_str_add(t_print_str *p, char *add)
{
	char	*new_str;
	size_t	new_len;

	if (add)
	{
		new_len = ft_strlen(add);
//		dprintf(g_state.fd, "%zu %zu %zu\r\n", new_len, p->len, p->count);
		if (new_len + p->len > PRINT_BUFF_SIZE * p->count)
		{
			p->count++;
//			dprintf(g_state.fd, "oh\r\n");
			new_str = (char *) malloc(sizeof(char) * ((PRINT_BUFF_SIZE + 1) * p->count));
			if (!new_str)
			{
//				dprintf(g_state.fd, "malloc failed\r\n");
				return (0);
			}
			ft_strcpy(new_str, p->str);
//			dprintf(g_state.fd, "oh wow\r\n");
			ft_strdel(&(p->str));
			p->str = new_str;
		}
		ft_strcpy(p->str + p->len, add);
		p->len += new_len;
	}
	return (1);
//	ft_strdel(&(p->str));
//	p->str = new_str;
}

static int	initialise_print_struct(t_print_str *p)
{
//	p->str = ft_strdup(CLEAR_SCRN_SET_YELLOW);
//	if (!p->str)
//		return (0);
	p->str = (char *) malloc(sizeof(char) * (PRINT_BUFF_SIZE + 1));
	ft_strcpy(p->str, CLEAR_SCRN_SET_YELLOW);
	p->len = ft_strlen(p->str);
	p->count = 1;
	return (1);
}

static char	*option_format(t_option_data *data)
{
	if (data->selected && !data->cursor)
		return (REV_VIDEO);
	else if (data->cursor && !data->selected)
		return (UL_START);
	else if (data->cursor && data->selected)
		return (UL_REV_VIDEO_START);
	return (NULL);
}

void	print_options(t_list *options, t_window_info *w)
{
	int				i;
	int				current_col;
	t_print_str		p;
	t_option_data	*data;

	if (!get_window_info(w, options))
		return ;
	if (!initialise_print_struct(&p))
		return ;
	current_col = 1;
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		if (!print_str_add(&p, position_cursor_in_window(*w, i, &current_col)))
			return ;
		if (!print_str_add(&p, option_format(data)))
			return ;
		if (!print_str_add(&p, data->name))
			return ;
		if (data->selected || data->cursor)
		{
			if (!print_str_add(&p, RESET_DEFAULT_COLOUR))
				return ;
		}
		options = options->next;
		i++;
	}
	write(g_state.fd, p.str, p.len);
	free(p.str);
}
