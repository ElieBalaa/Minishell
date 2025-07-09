/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_prompt(void)
{
	write(STDOUT_FILENO, "heredoc> ", 9);
}

int	find_last_delimiter_index(char **delimiters)
{
	int	last_index;

	if (!delimiters)
		return (-1);
	last_index = 0;
	while (delimiters[last_index])
		last_index++;
	return (last_index - 1);
}

int	process_multiple_heredocs(t_minishell *sh, char **delimiters,
		int *pipe_fd)
{
	int		i;
	char	*line;
	char	*expanded_line;

	if (!sh || !delimiters || !pipe_fd)
		return (-1);
	i = 0;
	while (delimiters[i])
	{
		while (1)
		{
			heredoc_prompt();
			line = read_heredoc_line(0);
			if (!line)
				return (-1);
			if (check_delimiter_match(line, delimiters[i]))
			{
				free(line);
				break ;
			}
			expanded_line = expand_vars(sh, line);
			write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
			write(pipe_fd[1], "\n", 1);
			free(line);
			free(expanded_line);
		}
		i++;
	}
	return (0);
}

int	process_heredoc(t_minishell *sh, char *delimiter)
{
	int	pipe_fd[2];

	if (!sh || !delimiter || pipe(pipe_fd) == -1)
		return (-1);
	handle_heredoc_loop(sh, delimiter, pipe_fd, 0);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
