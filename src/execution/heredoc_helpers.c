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

static int	is_delimiter_match(char *line, char *delimiter)
{
	size_t	line_len;
	size_t	delim_len;

	if (!line || !delimiter)
		return (0);
	line_len = ft_strlen(line);
	delim_len = ft_strlen(delimiter);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	return (line_len == delim_len
		&& ft_strncmp(line, delimiter, delim_len) == 0);
}

static char	*expand_line_buffer(char *line, size_t *capacity)
{
	if (*capacity == 0)
		*capacity = 64;
	else
		*capacity = *capacity * 2;
	line = ft_realloc(line, *capacity);
	return (line);
}

int	check_delimiter_match(char *line, char *delimiter)
{
	return (is_delimiter_match(line, delimiter));
}

char	*expand_buffer(char *line, size_t *capacity)
{
	return (expand_line_buffer(line, capacity));
}
