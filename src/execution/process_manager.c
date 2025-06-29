/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
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

static void	child_process(const char *cmd_path, char **argv)
{
	if (execve(cmd_path, argv, environ) == -1)
	{
		perror("minishell: execve");
		exit(127);
	}
}

static int	parent_process(pid_t pid)
{
	int	status;
	int	exit_code;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	fork_and_execute(const char *cmd_path, char **argv)
{
	pid_t	pid;

	if (!cmd_path || !argv)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		child_process(cmd_path, argv);
	}
	else
	{
		return (parent_process(pid));
	}
	return (0);
}
