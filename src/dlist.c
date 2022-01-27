/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:05:39 by clala             #+#    #+#             */
/*   Updated: 2021/02/13 21:56:37 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*t_dlist_new(void)
{
	t_dlist		*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	new->size = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}

t_dlist_node	*t_dlist_pop(t_dlist *list, t_dlist_node *node)
{
	if (!node->prev)
		list->head = node->next;
	else
		node->prev->next = node->next;
	if (!node->next)
		list->tail = node->prev;
	else
		node->next->prev = node->prev;
	if (node->next == node && node->prev == node)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	if (list->size > 0) {
		list->size--;
	}
	return (node);
}

t_dlist	*t_dlist_remove_node(t_dlist *list, t_dlist_node *node)
{
	t_dlist_pop(list, node);
	free(node);
	return (list);
}

t_dlist_node	*t_dlist_get_by_val(t_dlist *list, void *value)
{
	t_dlist_node	*tmp;

	tmp = list->head;
	while (tmp != NULL)
	{
		if (!memcmp(tmp->data, value, tmp->data_size))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

t_dlist_node	*t_dlist_get_by_index(t_dlist *list, int index)
{
	t_dlist_node	*tmp;
	int		i;

	tmp = list->head;
	while (tmp != NULL && i++ != index)
	{
		tmp = tmp->next;
	}
	return tmp;
}
