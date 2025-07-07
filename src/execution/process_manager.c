/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 23:26:11 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

static void	child_process(const char *path, char **argv, char **envp)
{
	if (execve(path, argv, envp) == -1)
	{
		perror("minishell: execve");
		exit(127);
	}
}

static int	parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	fork_and_execute(t_minishell *sh, const char *path, char **argv)
{
	pid_t	pid;

	if (!path || !argv)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_process(path, argv, sh->env);
	return (parent_process(pid));
}
