/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:01:52 by amann             #+#    #+#             */
/*   Updated: 2022/09/05 17:06:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
 * The process here is to cycle through the list until we hit the cursor node
 * and then delete that node, freeing it and it's consituent parts from memory.
 * If the first node in the list is being deleted, we can reset our list
 * pointer to the second node before deleteing.
 * If we are deleting a node in the middle of the list, the previous node's
 * next variable should be pointed the node after the deleted node.
 * If we are deleting the last node in the list, the previous node's next
 * variable should be set to NULL.
 */

static void	delete_first(t_list *current, t_option_data *data, t_list **options)
{
	t_list	*temp;

	temp = current->next;
	ft_lstdelone(&current, &delete_node);
	*options = temp;
	if (*options)
	{
		data = (t_option_data *)(*options)->content;
		data->cursor = TRUE;
	}
}

static void	delete_middle_or_end(t_list *current, t_list **options)
{
	t_option_data	*data;
	t_list			*temp;

	temp = current->next->next;
	ft_lstdelone(&(current->next), &delete_node);
	current->next = temp;
	if (temp)
		data = (t_option_data *) current->next->content;
	else
		data = (t_option_data *) (*options)->content;
	data->cursor = TRUE;
}

void	handle_delete(t_list **options)
{
	t_option_data	*data;
	t_list			*current;

	current = *options;
	data = (t_option_data *) current->content;
	if (data->cursor)
		delete_first(current, data, options);
	else
	{
		while (current->next)
		{
			data = (t_option_data *) current->next->content;
			if (data->cursor)
			{
				delete_middle_or_end(current, options);
				break ;
			}
			current = current->next;
		}
	}
	setup_window();
}
