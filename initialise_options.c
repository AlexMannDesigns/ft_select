/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:43:14 by amann             #+#    #+#             */
/*   Updated: 2022/09/07 15:20:41 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 *	each sub-struct of our linked list will contain the name of the option,
 *	which will be displayed in the terminal, and an int initialised to FALSE
 *	as this will always not be selected when the program starts.
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

void	initialise_options(t_list **options, char **argv)
{
	size_t	i;
	int		first;
	t_list *current_node;

	*options = (t_list *) ft_memalloc(sizeof(t_list));
	if (!(*options))
	{
		//free list and set options to NULL
		ft_lstdel(options, &(delete_node));
		return ;
	}
	current_node = *options;
	first = TRUE;
	i = 0;
	while (argv[i])
	{
		//create options struct in current node
		(current_node)->content = (void *) create_option_data_struct(argv[i], &first);
		if (!((current_node)->content))
		{
			//free list and set options to NULL
			ft_lstdel(options, &(delete_node));
			return ;
		}
		//content size will always be the size of an option_data struct
		current_node->content_size = sizeof(t_option_data);
		current_node->next = NULL;
		//check if list will continue and allocate mem if appropriate
		if (argv[i + 1])
		{
			current_node->next = (t_list *) ft_memalloc(sizeof(t_list));
			if (!current_node)
			{
				//free list and set options to NULL
				ft_lstdel(options, &(delete_node));
				return ;
			}
		}
		current_node = current_node->next;
		i++;
	}
/*	ft_printf("current : %p | original : %p\n", (void *) current_node, (void *) *options);
	t_option_data *current_data;
	current_node = *options;
	while (current_node)
	{
		current_data = (t_option_data *) (current_node)->content;
		ft_printf("%s\n", current_data->name);
		current_node = (current_node)->next;
	}
	*/
}
