/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_interactive_content(char **content, char *delimiter,
		int is_last, int is_piped)
{
	*content = NULL;
	if (!is_piped)
		heredoc_prompt();
	return (handle_interactive_loop(content, delimiter, is_last, is_piped));
}

int	process_piped_content(char **content, char **current_pos,
		char *delimiter)
{
	char	*delim_pos;
	size_t	content_size;
	size_t	content_capacity;
	char	*line;

	if (!content || !current_pos || !delimiter)
		return (-1);
	delim_pos = *current_pos;
	content_size = 0;
	content_capacity = 0;
	*content = NULL;
	while (delim_pos && *delim_pos)
	{
		line = extract_line(current_pos);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			return (0);
		}
		if (!append_content_line(content, line, &content_size,
				&content_capacity))
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	handle_heredoc_loop(t_minishell *sh, char *delimiter,
		int *pipe_fd, int is_piped)
{
	char	*line;
	char	*expanded_line;

	if (!sh || !delimiter || !pipe_fd)
		return (-1);
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
		expanded_line = expand_vars(sh, line);
		if (expanded_line)
		{
			write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
			write(pipe_fd[1], "\n", 1);
			free(expanded_line);
		}
		free(line);
	}
	return (0);
}

int	process_delimiter_content(t_delimiter_content_params *params)
{
	char	*line;

	while (1)
	{
		if (!params->is_piped)
			heredoc_prompt();
		line = read_heredoc_line(params->is_piped);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, params->delimiter))
		{
			free(line);
			break ;
		}
		if (params->is_last)
		{
			if (!append_expanded_line(params->sh, line, params->vars))
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	return (0);
}

int	init_heredoc_vars(char **delimiters, int *i, int *last_index,
		int *is_piped)
{
	*i = 0;
	*last_index = find_last_delimiter_index(delimiters);
	if (*last_index < 0)
		return (-1);
	*is_piped = !isatty(STDIN_FILENO);
	return (0);
}
