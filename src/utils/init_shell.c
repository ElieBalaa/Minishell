/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:40:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 19:13:59 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	init_minishell(t_minishell *sh, char **envp)
// {
// 	size_t	n;
// 	size_t	i;

// 	gc_init(sh);
// 	n = 0;
// 	while (envp[n])
// 		n++;
// 	sh->env = malloc(sizeof(char *) * (n + 1));
// 	if (!sh->env)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (i < n)
// 	{
// 		sh->env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	sh->env[n] = NULL;
// 	sh->last_exit = 0;
// }
void init_minishell(t_minishell *sh, char **envp)
{
    size_t n = 0, i;

    gc_init(sh);
    while (envp[n]) n++;
    sh->env = malloc(sizeof(char *) * (n + 1));
    if (!sh->env)
        exit(EXIT_FAILURE);
    for (i = 0; i < n; ++i)
        sh->env[i] = ft_strdup(envp[i]);
    sh->env[n] = NULL;

    sh->last_exit     = 0;
    sh->is_interactive = isatty(STDIN_FILENO);
    sh->child_pid      = -1;
}