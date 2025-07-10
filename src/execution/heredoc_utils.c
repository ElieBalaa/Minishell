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

char	*extract_line(char **current_pos)
{
	char	*start;
	char	*end;
	char	*line;
	int		len;

	if (!current_pos || !*current_pos)
		return (NULL);
	start = *current_pos;
	end = ft_strchr(start, '\n');
	if (end)
	{
		len = end - start;
		line = ft_strndup(start, len);
		*current_pos = end + 1;
	}
	else
	{
		len = ft_strlen(start);
		line = ft_strndup(start, len);
		*current_pos = NULL;
	}
	return (line);
}

int	check_delimiter_match(char *line, char *delimiter)
{
	int	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\0')
		return (1);
	return (0);
}

int	append_content_line(char **content, char *line, size_t *content_size,
		size_t *content_capacity)
{
	size_t	line_len;
	size_t	new_capacity;
	char	*new_content;

	if (!content || !line || !content_size || !content_capacity)
		return (0);
	line_len = ft_strlen(line);
	if (*content_size + line_len + 1 >= *content_capacity)
	{
		if (*content_capacity == 0)
			new_capacity = 1024;
		else
			new_capacity = *content_capacity * 2;
		new_content = ft_realloc(*content, new_capacity);
		if (!new_content)
			return (0);
		*content = new_content;
		*content_capacity = new_capacity;
	}
	ft_memcpy(*content + *content_size, line, line_len);
	*content_size += line_len;
	(*content)[*content_size] = '\0';
	return (1);
}

int	append_temp_content(char **temp_content, char *line, size_t *temp_size,
		size_t *temp_capacity)
{
	return (append_content_line(temp_content, line, temp_size, temp_capacity));
}

void	finalize_content(char **content, char **temp_content, size_t *temp_size)
{
	if (!content || !temp_content)
		return ;
	*content = *temp_content;
	*temp_content = NULL;
	(void)temp_size;
}
