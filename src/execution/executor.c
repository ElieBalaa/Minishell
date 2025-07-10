/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 18:29:07 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

static int	exec_one(t_minishell *sh, t_ast *n)
{
	char	*path;
	int		st;

	if (!n || !n->cmd || !n->cmd[0])
		return (1);
	st = execute_builtin(sh, n->cmd);
	if (st != -1)
		return (st);
	path = resolve_command_path(sh, n->cmd[0]);
	if (!path)
	{
		printf("minishell: %s: command not found\n", n->cmd[0]);
		return (127);
	}
	st = fork_and_execute(sh, path, n->cmd, n);
	free(path);
	return (st);
}

static int	exec_list(t_minishell *sh, t_ast *n)
{
	int	st;

	st = 0;
	while (n)
	{
		st = exec_one(sh, n);
		sh->last_exit = st;
		n = n->right;
	}
	return (st);
}

int	execute_ast(t_minishell *sh, t_ast *ast)
{
	if (!ast)
		return (0);
	return (exec_list(sh, ast));
}
