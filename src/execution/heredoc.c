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

static char	*init_full_input(int is_piped, size_t *full_size,
			size_t *full_capacity)
{
	char	*full_input;
	char	*line;

	full_input = NULL;
	*full_size = 0;
	*full_capacity = 0;
	if (is_piped)
	{
		while (1)
		{
			line = read_heredoc_line(is_piped);
			if (line == NULL)
				break ;
			if (!append_line_to_input(&full_input, line, full_size,
					full_capacity))
			{
				free(line);
				return (NULL);
			}
			free(line);
		}
	}
	return (full_input);
}

int	find_last_delimiter_index(char **delimiters)
{
	int	last_index;

	last_index = 0;
	while (delimiters[last_index])
		last_index++;
	last_index--;
	return (last_index);
}

int	process_multiple_heredocs(t_minishell *sh, char **delimiters,
			int *pipe_fd)
{
	size_t	full_size;
	size_t	full_capacity;
	char	*full_input;

	full_input = init_full_input(!isatty(STDIN_FILENO), &full_size,
			&full_capacity);
	if (!isatty(STDIN_FILENO) && !full_input)
		return (-1);
	return (process_content(sh, delimiters, pipe_fd, full_input));
}

int	process_heredoc(t_minishell *sh, char *delimiter)
{
	int	pipe_fd[2];
	int	is_piped;

	if (!sh || !delimiter || pipe(pipe_fd) == -1)
		return (-1);
	is_piped = !isatty(STDIN_FILENO);
	handle_heredoc_loop(sh, delimiter, pipe_fd, is_piped);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
