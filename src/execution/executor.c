/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 00:15:46 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

static int	setup_heredoc_input(t_minishell *sh, t_ast *node)
{
	int	heredoc_fd;

	if (!node->is_heredoc || !node->heredoc_delim)
		return (0);
	heredoc_fd = process_heredoc(sh, node->heredoc_delim);
	if (heredoc_fd == -1)
		return (-1);
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		close(heredoc_fd);
		return (-1);
	}
	close(heredoc_fd);
	return (0);
}

static int	setup_input_redirect(t_minishell *sh, t_ast *node)
{
	int	input_fd;

	if (!node)
		return (0);
	if (node->is_heredoc)
		return (setup_heredoc_input(sh, node));
	if (!node->input)
		return (0);
	input_fd = open(node->input, O_RDONLY);
	if (input_fd == -1)
		return (-1);
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		close(input_fd);
		return (-1);
	}
	close(input_fd);
	return (0);
}

static int	exec_one(t_minishell *sh, t_ast *n)
{
	char	*path;
	int		st;

	if (!n || !n->cmd || !n->cmd[0])
		return (1);
	if (setup_input_redirect(sh, n) == -1)
		return (1);
	st = execute_builtin(sh, n->cmd);
	if (st != -1)
		return (st);
	path = resolve_command_path(n->cmd[0]);
	if (!path)
	{
		printf("minishell: %s: command not found\n", n->cmd[0]);
		return (127);
	}
	st = fork_and_execute(sh, path, n->cmd);
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
