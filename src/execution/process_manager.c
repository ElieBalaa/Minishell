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

int	setup_output_redirect(t_ast *node);

static void	child_process(t_child_args *args)
{
	if (args->node && setup_input_redirect(args->sh, args->node) == -1)
		exit(1);
	if (args->node && setup_output_redirect(args->node) == -1)
		exit(1);
	if (execve(args->path, args->argv, args->envp) == -1)
	{
		perror("minishell: execve");
		exit(127);
	}
}

static int	parent_process(t_minishell *sh, pid_t pid)
{
	int	status;

	sh->child_pid = pid;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		sh->child_pid = 0;
		return (1);
	}
	sh->child_pid = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	fork_and_execute(t_minishell *sh, const char *path,
		char **argv, t_ast *node)
{
	pid_t			pid;
	t_child_args	args;

	if (!path || !argv)
		return (1);
	args.path = path;
	args.argv = argv;
	args.envp = sh->env;
	args.sh = sh;
	args.node = node;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_process(&args);
	return (parent_process(sh, pid));
}
