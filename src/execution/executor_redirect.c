/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int	setup_heredoc_input(t_minishell *sh, t_ast *node)
{
	int	pipe_fd[2];

	if (!node->is_heredoc || !node->heredoc_delims)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (-1);
	if (process_multiple_heredocs(sh, node->heredoc_delims, pipe_fd) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

int	setup_input_redirect(t_minishell *sh, t_ast *node)
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

int	setup_output_redirect(t_ast *node)
{
	int	output_fd;
	int	flags;

	if (!node || !node->output)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (node->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	output_fd = open(node->output, flags, 0644);
	if (output_fd == -1)
		return (-1);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		close(output_fd);
		return (-1);
	}
	close(output_fd);
	return (0);
}
