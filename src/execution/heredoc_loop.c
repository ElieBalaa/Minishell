/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_line_to_pipe(int *pipe_fd, char *line)
{
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	return (0);
}

static int	process_heredoc_line(t_minishell *sh, char *line,
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

int	handle_heredoc_loop(t_minishell *sh, char *delimiter,
		int *pipe_fd, int is_piped)
{
	char	*line;
	int		is_quoted;

	if (!sh || !delimiter || !pipe_fd)
		return (-1);
	is_quoted = (delimiter[0] == '\'' || delimiter[0] == '\"');
	while (1)
	{
		if (!is_piped)
			heredoc_prompt();
		line = read_heredoc_line(is_piped);
		if (!line)
			break ;
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(sh, line, pipe_fd, is_quoted) == -1)
			return (-1);
	}
	return (0);
}
