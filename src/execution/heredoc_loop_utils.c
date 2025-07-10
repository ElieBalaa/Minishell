/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/07/10 21:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_line_to_pipe(int *pipe_fd, char *line)
{
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	return (0);
}

int	process_heredoc_line(t_minishell *sh, char *line,
		int *pipe_fd, int is_quoted)
{
	char	*expanded_line;

	if (is_quoted)
		return (write_line_to_pipe(pipe_fd, line));
	expanded_line = expand_vars(sh, line);
	if (expanded_line)
	{
		write_line_to_pipe(pipe_fd, expanded_line);
		free(expanded_line);
	}
	free(line);
	return (0);
}

int	is_delimiter_quoted(char *delimiter)
{
	int	len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len < 2)
		return (0);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
		return (1);
	return (0);
}

int	setup_iteration_args(t_setup_args *setup, t_iteration_args *iter_args)
{
	iter_args->sh = setup->args->sh;
	iter_args->line = setup->line;
	iter_args->clean_delim = setup->clean_delim;
	iter_args->pipe_fd = setup->args->pipe_fd;
	iter_args->is_quoted = setup->is_quoted;
	return (0);
}

int	is_originally_quoted(const char *delimiter)
{
	if (delimiter && delimiter[0] == '\'')
		return (1);
	return (0);
}
