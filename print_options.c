/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:12:57 by amann             #+#    #+#             */
/*   Updated: 2022/09/14 12:40:20 by amann            ###   ########.fr       */
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

char	*create_cursor_coord_str(int y, int x)
{
	char	*y_str;
	char	*x_str;
	char	*res;
	size_t	x_len;
	size_t	y_len;
	size_t	len;

	y_str = ft_itoa(y);
	x_str = ft_itoa(x);
	if (!y_str || !x_str)
		return (NULL);
	x_len = ft_strlen(x_str);
	y_len = ft_strlen(y_str);
	len = x_len + y_len + 2;
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	char *temp, *temp2, *temp3;

	temp = ft_strjoin(y_str, ";");
	temp2 = ft_strjoin(x_str, "H");
	temp3 = ft_strjoin(temp, temp2);
	ft_strcpy(res, "\033[");
	ft_strcpy(res + 2, temp3);
//	res[2 + y_len] = ';';
//	ft_strcpy(res + 3 + y_len, x_str);
//	res[ft_strlen(res) - 1] = 'H';
	free(y_str);
	free(x_str);
	free(temp);
	free(temp2);
	free(temp3);
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
		w->col_height = w->len;
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

	new_str = ft_strjoin(p->str, add);
	if (!new_str)
		return ;
	p->len = p->len += ft_strlen(add);
	ft_strdel(&(p->str));
	p->str = new_str;
}

void	position_cursor_in_window(t_window_info w, int i, int *current_col, t_print_str *p)
{
	int			x;
	int			y;
	char		*temp;

	if (w.len < w.rows)
	{
		//position_term_cursor(i + 1, 0);
		temp = create_cursor_coord_str(i + 1, 0);
		print_str_add(p, temp);
		//ft_putstr_fd(temp, g_state.fd);
		free(temp);
		return ;
	}
	if (i >= (*current_col * w.col_height))
		(*current_col)++;
	x = (*current_col - 1) * w.col_width;
	if (i < w.col_height)
		y = i + 1;
	else
		y = i - ((*current_col - 1) * w.col_height) + 1;
	//position_term_cursor(y, x);
	temp = create_cursor_coord_str(y, x);
	print_str_add(p, temp);
	//	ft_putstr_fd(temp, g_state.fd);
	free(temp);
}


void	print_options(t_list *options, t_window_info *w)
{
	int				i;
	int				current_col;
	t_print_str		p;
	t_option_data	*data;

	if (!get_window_info(w, options))
		return ;
	p.str = ft_strdup(CLEAR_SCRN);
	p.len = ft_strlen(p.str);
	current_col = 1;
	i = 0;
	while (options)
	{
		data = (t_option_data *) options->content;
		position_cursor_in_window(*w, i, &current_col, &p);
		if (data->selected)
			print_str_add(&p, REV_VIDEO);
		if (data->cursor)
			print_str_add(&p, UL_START);
		print_str_add(&p, YELLOW);
		print_str_add(&p, data->name);
		print_str_add(&p, RESET_COLOUR);
		options = options->next;
		i++;
	}
	write(g_state.fd, p.str, p.len);
	free(p.str);
	g_state.window_change = FALSE;
}
