/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/15 16:13:20 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


static int	get_max_option_length(t_list *options)
{
	int max;
	t_option_data *current;

	max = 0;
	while (options)
	{
		current = (t_option_data *) options->content;
		if ((int) current->len > max)
			max = current->len;
		options = options->next;
	}
	return (max);
}

int		find_x(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'X')
			break ;
		i++;
	}
	return (i);
}

char *insert_y(char *y_str)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin("\033[", y_str);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, ";XH");
	if (!res)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (res);
}

char	*insert_x(char *res, int i, size_t x_len, char *x_str)
{
	char	*temp;
	char	*temp2;
	char	*new_res;

	temp = ft_strndup(res, i);
	temp2 = ft_strnew(x_len + 1);
	free(res);
	if (!temp || !temp2)
	{
		free(temp);
		free(temp2);
		return (NULL);
	}
	ft_strcpy(temp2, x_str);
	temp2[x_len] = 'H';
	new_res = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (new_res);
}

char	*construct_str(char	*y_str, char *x_str, size_t y_len, size_t x_len)
{
	char	*res;
	int		i;

	res = ft_strdup("\033[X;XH");
	if (!res)
		return (NULL);
	i = find_x(res);
	if (y_len == 1)
		res[i] = y_str[0];
	else
	{
		free(res);
		res = insert_y(y_str);
	}
	i = find_x(res);
	if (x_len == 1)
		res[i] = x_str[0];
	else
		res = insert_x(res, i, x_len, x_str);
	return (res);
}

char	*create_cursor_coord_str(int y, int x)
{
	char	*y_str;
	char	*x_str;
	char	*res;
	size_t	x_len;
	size_t	y_len;

	y_str = ft_itoa(y);
	x_str = ft_itoa(x);
	if (!y_str || !x_str)
		return (NULL);
	x_len = ft_strlen(x_str);
	y_len = ft_strlen(y_str);
	res = construct_str(y_str, x_str, y_len, x_len);
	return (res);
}

int	get_window_info(t_window_info *w, t_list *options)
{
	w->len = (int) ft_list_len(options);
	if (w->len == 0)
		return (0);
	get_cols_rows(&(w->cols), &(w->rows));
	w->col_width = get_max_option_length(options) + 3;
	w->cols_to_display = (w->cols / w->col_width);
	if (w->cols_to_display == 0)
		w->cols_to_display = 1;
	if (w->len < w->rows)
	{
		w->col_height = w->len;
		w->cols_to_display = 1;
	}
	else
		w->col_height = (w->len / w->cols_to_display) + 1;
	if (w->col_height >= w->rows || w->col_width > w->cols)
	{
		position_term_cursor(1, 1);
		ft_putstr_fd(CLEAR_SCRN, g_state.fd);
		ft_putstr_fd("Make me bigger!!!", g_state.fd);
		return (0);
	}
	return (1);
}

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
	char		*res;

	if (w.len < w.rows)
	{
		res = create_cursor_coord_str(i + 1, 0);
		return (res);
	}
	if (i >= (*current_col * w.col_height))
		(*current_col)++;
	x = (*current_col - 1) * w.col_width;
	if (i < w.col_height)
		y = i + 1;
	else
		y = i - ((*current_col - 1) * w.col_height) + 1;
	res = create_cursor_coord_str(y, x);
	return (res);
}


void	print_options(t_list *options, t_window_info *w)
{
	int				i;
	int				current_col;
	char			*temp;
	t_print_str		p;
	t_option_data	*data;

	if (!get_window_info(w, options))
		return ;
	p.str = ft_strdup(CLEAR_SCRN_SET_YELLOW);
	p.len = ft_strlen(p.str);
	current_col = 1;
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		temp = position_cursor_in_window(*w, i, &current_col);
		print_str_add(&p, temp);
		free(temp);
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
	g_state.window_change = FALSE;
}
