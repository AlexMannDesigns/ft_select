/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 14:29:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	print_str_add(t_print_str *p, char *add)
{
	char	*new_str;
	size_t	new_len;
	size_t	size;

	if (add)
	{
		new_len = ft_strlen(add);
		if (new_len + p->len > PRINT_BUFF_SIZE * p->count)
		{
			p->count++;
			size = sizeof(char) * ((PRINT_BUFF_SIZE + 1) * p->count);
			new_str = (char *) malloc(size);
			if (!new_str)
				return (0);
			ft_strcpy(new_str, p->str);
			ft_strdel(&(p->str));
			p->str = new_str;
		}
		ft_strcpy(p->str + p->len, add);
		p->len += new_len;
	}
	return (1);
}

static int	initialise_print_struct(t_print_str *p)
{
	p->str = (char *) malloc(sizeof(char) * (PRINT_BUFF_SIZE + 1));
	ft_strcpy(p->str, CLEAR_SCRN_SET_YELLOW);
	p->len = ft_strlen(p->str);
	p->count = 1;
	return (1);
}

static char	*option_format(t_option_data *data)
{
	if (data->selected || data->cursor)
	{
		if (data->selected && !data->cursor)
			return (REV_VIDEO);
		else if (data->cursor && !data->selected)
			return (UL_START);
		else if (data->cursor && data->selected)
			return (UL_REV_VIDEO_START);
	}
	return (NULL);
}

static int	build_str(t_print_str *p, t_window_info *w, int i, t_option_data *d)
{
	if (!print_str_add(p, position_cursor_in_window(w, i)))
		return (0);
	if (!print_str_add(p, option_format(d)))
		return (0);
	if (!print_str_add(p, d->name))
		return (0);
	if (d->selected || d->cursor)
	{
		if (!print_str_add(p, RESET_DEFAULT_COLOUR))
			return (0);
	}
	return (1);
}

void	print_options(t_list *options, t_window_info *w)
{
	int				i;
	t_print_str		p;
	t_option_data	*data;

	if (!get_window_info(w, options))
		return ;
	if (!initialise_print_struct(&p))
		return ;
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		if (!build_str(&p, w, i, data))
			return ;
		options = options->next;
		i++;
	}
	write(g_state.fd, p.str, p.len);
	free(p.str);
}
