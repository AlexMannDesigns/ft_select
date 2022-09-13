/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:43:14 by amann             #+#    #+#             */
/*   Updated: 2022/09/13 13:29:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 *	each sub-struct of our linked list will contain the name of the option,
 *	which will be displayed in the terminal, and an int initialised to FALSE
 *	as this will always not be selected when the program starts.
 *
 *	No memory needs to be freed here because if something goes wrong we return
 *	NULL and the whole list gets deleted.
 */

static t_option_data	*create_option_data_struct(char *option_name, int *first)
{
	t_option_data	*new;

	new = (t_option_data *) ft_memalloc(sizeof(t_option_data));
	if (!new)
		return (NULL);
	new->name = ft_strdup(option_name);
	if (!(new->name))
		return (NULL);
	new->len = ft_strlen(option_name);
	new->selected = FALSE;
	if (*first)
	{
		new->cursor = TRUE;
		*first = FALSE;
	}
	else
		new->cursor = FALSE;
	return (new);

}

static int	delete_list(t_list **options)
{
	ft_lstdel(options, &(delete_node));
	return (0);
}

int		initialise_options(t_list **options, char **argv)
{
	int		first;
	t_list *current_node;

	*options = (t_list *) ft_memalloc(sizeof(t_list));
	if (!(*options))
		return (delete_list(options));
	current_node = *options;
	first = TRUE;
	while (*argv)
	{
		current_node->content = (void *) create_option_data_struct(*argv, &first);
		if (!(current_node->content))
			return (delete_list(options));
		current_node->content_size = sizeof(t_option_data);
		current_node->next = NULL;
		if (argv[1])
		{
			current_node->next = (t_list *) ft_memalloc(sizeof(t_list));
			if (!current_node)
				return (delete_list(options));
		}
		current_node = current_node->next;
		argv++;
	}
	return (1);
}
