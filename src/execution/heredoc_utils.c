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

/*
void	heredoc_prompt(void)
{
	write(STDOUT_FILENO, "> ", 2);
}

int	find_last_delimiter_index(char **delimiters)
{
	int	index;

	index = 0;
	while (delimiters[index])
		index++;
	return (index - 1);
}
*/

int	check_delimiter_match(char *line, char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\0')
		return (1);
	return (0);
}

static char	*read_line_from_pipe(void)
{
	char	buffer[1024];
	char	*line;
	int	bytes_read;
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
			break;
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	if (line)
		line[total_read] = '\0';
	return (line);
}

char	*read_heredoc_line(int is_piped)
{
	char	*line;

	if (is_piped)
		line = read_line_from_pipe();
	else
		line = readline("> ");
	if (!line)
		return (NULL);
	return (line);
}

char	*extract_line(char **current_pos)
{
	char	*start;
	char	*end;
	char	*line;
	size_t	len;

	start = *current_pos;
	end = start;
	while (*end && *end != '\n')
		end++;
	len = end - start;
	line = ft_strndup(start, len);
	if (*end == '\n')
		end++;
	*current_pos = end;
	return (line);
}

int	append_content_line(char **content, char *line, size_t *content_size,
		size_t *content_capacity)
{
	size_t	line_len;
	size_t	new_capacity;
	char	*new_content;

	line_len = ft_strlen(line);
	if (*content_size + line_len + 1 >= *content_capacity)
	{
		new_capacity = *content_capacity == 0 ? 1024 : *content_capacity * 2;
		new_content = ft_realloc(*content, new_capacity);
		if (!new_content)
			return (0);
		*content = new_content;
		*content_capacity = new_capacity;
	}
	ft_memcpy(*content + *content_size, line, line_len);
	*content_size += line_len;
	(*content)[*content_size] = '\n';
	*content_size += 1;
	(*content)[*content_size] = '\0';
	return (1);
}

int	append_temp_content(char **temp_content, char *line, size_t *temp_size,
		size_t *temp_capacity)
{
	size_t	line_len;
	size_t	new_capacity;
	char	*new_content;

	line_len = ft_strlen(line);
	if (*temp_size + line_len + 1 >= *temp_capacity)
	{
		new_capacity = *temp_capacity == 0 ? 1024 : *temp_capacity * 2;
		new_content = ft_realloc(*temp_content, new_capacity);
		if (!new_content)
			return (0);
		*temp_content = new_content;
		*temp_capacity = new_capacity;
	}
	ft_memcpy(*temp_content + *temp_size, line, line_len);
	*temp_size += line_len;
	(*temp_content)[*temp_size] = '\n';
	*temp_size += 1;
	(*temp_content)[*temp_size] = '\0';
	return (1);
}

void	finalize_content(char **content, char **temp_content, size_t *temp_size)
{
	*content = *temp_content;
	*temp_content = NULL;
	*temp_size = 0;
}
