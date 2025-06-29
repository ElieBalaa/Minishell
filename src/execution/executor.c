/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/02 14:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

static int	execute_single_command(t_ast *node)
{
	char	*cmd_path;
	int		status;

	if (!node || !node->cmd || !node->cmd[0])
		return (1);
	status = execute_builtin(node->cmd);
	if (status != -1)
		return (status);
	cmd_path = resolve_command_path(node->cmd[0]);
	if (!cmd_path)
	{
		printf("minishell: %s: command not found\n", node->cmd[0]);
		return (127);
	}
	status = fork_and_execute(cmd_path, node->cmd);
	return (status);
}

static int	execute_pipeline_node(t_ast *node)
{
	int	status;

	status = 0;
	while (node)
	{
		status = execute_single_command(node);
		node = node->right;
	}
	return (status);
}

int	execute_ast(t_ast *ast)
{
	if (!ast)
		return (0);
	return (execute_pipeline_node(ast));
}
