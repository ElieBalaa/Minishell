/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/09 10:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	gc_cleanup_all(t_minishell *sh)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!sh)
		return ;
	current = sh->gc.head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	sh->gc.head = NULL;
	sh->gc.count = 0;
}

void	gc_free_nodes(t_minishell *sh)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!sh)
		return ;
	current = sh->gc.head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	sh->gc.head = NULL;
	sh->gc.count = 0;
}
