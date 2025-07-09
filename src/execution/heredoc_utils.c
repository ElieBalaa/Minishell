/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_line_from_pipe(void)
{
	char	buffer[1024];
	char	*line;
	int		bytes_read;
	size_t	total_read;

	line = NULL;
	total_read = 0;
	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		line = ft_realloc(line, total_read + bytes_read + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line + total_read, buffer, bytes_read);
		total_read += bytes_read;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	if (line)
		line[total_read] = '\0';
	return (line);
}

static char	*expand_buffer(char *line, size_t *capacity)
{
	if (*capacity == 0)
		*capacity = 64;
	else
		*capacity = *capacity * 2;
	line = ft_realloc(line, *capacity);
	return (line);
}

static char	*read_line_interactive(void)
{
	char	c;
	char	*line;
	size_t	len;
	size_t	capacity;

	line = NULL;
	len = 0;
	capacity = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (len >= capacity)
		{
			line = expand_buffer(line, &capacity);
			if (!line)
				return (NULL);
		}
		line[len++] = c;
		if (c == '\n')
			break ;
	}
	if (line)
		line[len] = '\0';
	return (line);
}

char	*read_heredoc_line(int is_piped)
{
	if (is_piped)
		return (read_line_from_pipe());
	else
		return (read_line_interactive());
}
