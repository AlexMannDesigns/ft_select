/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/16 17:53:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_str_add(t_print_str *p, char *add)
{
	char	*new_str;
	size_t	new_len;

	if (!add)
		return ;
	new_len = ft_strlen(add);
	new_str = (char *) malloc(new_len + p->len + 1);
	if (!new_str)
		return ;
	ft_strcpy(new_str, p->str);
	ft_strcpy(new_str + p->len, add);
	p->len += new_len;
	ft_strdel(&(p->str));
	p->str = new_str;
}

char	*position_cursor_in_window(t_window_info w, int i, int *current_col)
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

int	initialise_print_struct(t_print_str *p)
{
	p->str = ft_strdup(CLEAR_SCRN_SET_YELLOW);
	if (!p->str)
		return (0);
	p->len = ft_strlen(p->str);
	return (1);
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
		print_str_add(&p, position_cursor_in_window(*w, i, &current_col));
		if (data->selected && !data->cursor)
			print_str_add(&p, REV_VIDEO);
		else if (data->cursor && !data->selected)
			print_str_add(&p, UL_START);
		else if (data->cursor && data->selected)
			print_str_add(&p, UL_REV_VIDEO_START);
		print_str_add(&p, data->name);
		if (data->selected || data->cursor)
			print_str_add(&p, RESET_DEFAULT_COLOUR);
		options = options->next;
		i++;
	}
	write(g_state.fd, p.str, p.len);
	free(p.str);
}
