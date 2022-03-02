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

	i = 0;
	tmp = list->head;
	while (tmp != NULL && i++ != index)
	{
		tmp = tmp->next;
	}
	return tmp;
}

void	t_dlist_node_free(void (*free_func)(t_dlist_node *node),
						t_dlist_node *n)
{
	(*free_func)(n);
}

void	t_dlist_free_content(t_dlist *dlist,
						void (*free_func)(t_dlist_node *))
{
	t_dlist_node	*node;
	t_dlist_node	*next;

	node = dlist->head;
	(void)free_func;
	while (node)
	{
		next = node->next;
		t_dlist_node_free(free_func, node);
		node = next;
	}
}

void	t_dlist_free(t_dlist *dlist,
						void (*free_func)(t_dlist_node *))
{
	t_dlist_free_content(dlist, free_func);
	free(dlist);	
}

void	t_dlist_node_free_simple(t_dlist_node *node)
{
	free(node->data);
	free(node);
}

#include "dlist.h"

t_dlist_node	*t_dlist_node_new(void *data, int size)
{
	t_dlist_node	*new;

	new = (t_dlist_node *)malloc(sizeof(t_dlist_node));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	new->data_size = size;
	return (new);
}

/*
** Add new node and set it to the given pointer
*/

t_dlist_node	*t_dlist_insert_after(t_dlist *list,
t_dlist_node *node, t_dlist_node *new)
{
	new->prev = node;
	if (!node->next)
		list->tail = new;
	else
	{
		new->next = node->next;
		node->next->prev = new;
	}
	node->next = new;
	list->size++;
	return (new);
}

t_dlist_node	*t_dlist_insert_before(t_dlist *list,
t_dlist_node *node, t_dlist_node *new)
{
	new->next = node;
	if (!node->prev)
		list->head = new;
	else
	{
		new->prev = node->prev;
		node->prev->next = new;
	}
	node->prev = new;
	list->size++;
	return (new);
}

/*
** add to the front of the list
*/

t_dlist_node	*t_dlist_push(t_dlist *list, t_dlist_node *new)
{
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
		list->size++;
	}
	else
	{
		t_dlist_insert_before(list, list->head, new);
	}
	return (new);
}

/*
** add to the end of the list
*/

t_dlist_node	*t_dlist_append(t_dlist *list, t_dlist_node *new)
{
	if (!list->tail)
		t_dlist_push(list, new);
	else
		t_dlist_insert_after(list, list->tail, new);
	return (new);
}

#include <stdio.h>

void t_dlist_print_str(t_dlist *dlist)
{
    printf("dlist content:\n");
    t_dlist_node *tmp = dlist->head;
    while (tmp) {
        printf("%s\n", (char *)tmp->data);
        tmp = tmp->next;
    }
    printf("dlist content end\n");
}
