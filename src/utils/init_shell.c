/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:40:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 21:40:42 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_minishell(t_minishell *sh, char **envp)
{
	size_t	n;
	size_t	i;

	gc_init(sh);
	n = 0;
	while (envp[n])
		n++;
	sh->env = malloc(sizeof(char *) * (n + 1));
	if (!sh->env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		sh->env[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->env[n] = NULL;
	sh->last_exit = 0;
}
