/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:30:00 by the-flash        #+#    #+#             */
/*   Updated: 2025/07/10 19:30:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_piped_content(char **content, size_t *content_size,
		size_t *content_capacity)
{
	if (!content)
		return (-1);
	*content_size = 0;
	*content_capacity = 0;
	*content = NULL;
	return (0);
}

static int	process_piped_line(char **content, char *line,
		size_t *content_size, size_t *content_capacity)
{
	if (!append_content_line(content, line, content_size, content_capacity))
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

int	process_piped_content(char **content, char **current_pos,
		char *delimiter)
{
	char	*line;
	size_t	content_size;
	size_t	content_capacity;

	if (!content || !current_pos || !delimiter)
		return (-1);
	if (init_piped_content(content, &content_size, &content_capacity) == -1)
		return (-1);
	while (*current_pos && **current_pos)
	{
		line = extract_line(current_pos);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			return (0);
		}
		if (process_piped_line(content, line, &content_size,
				&content_capacity) == -1)
			return (-1);
	}
	return (0);
}

int	read_loop_line(t_delimiter_content_params *params,
		char **line, void (*old_handler)(int))
{
	if (!params->is_piped)
		heredoc_prompt();
	*line = read_heredoc_line(params->is_piped);
	if (!*line)
	{
		signal(SIGINT, old_handler);
		return (-1);
	}
	return (0);
}
