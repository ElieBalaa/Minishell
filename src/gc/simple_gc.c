/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/27 16:44:40 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_simple_gc	g_gc = {NULL, 0};

int	gc_init(void)
{
	g_gc.head = NULL;
	g_gc.count = 0;
	signal(SIGINT, gc_emergency_cleanup);
	signal(SIGTERM, gc_emergency_cleanup);
	atexit(gc_cleanup_all);
	return (1);
}

int	gc_add(void *ptr)
{
	t_gc_node	*new_node;

	if (!ptr)
		return (0);
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return (0);
	new_node->ptr = ptr;
	new_node->next = g_gc.head;
	g_gc.head = new_node;
	g_gc.count++;
	return (1);
}

void	gc_cleanup_all(void)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = g_gc.head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	g_gc.head = NULL;
	g_gc.count = 0;
}

void	gc_emergency_cleanup(int sig)
{
	gc_cleanup_all();
	exit(sig);
} 