/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_line_to_input(char **full_input, char *line, size_t *full_size,
		size_t *full_capacity)
{
	size_t	line_len;
	size_t	new_capacity;
	char	*new_input;

	line_len = ft_strlen(line);
	if (*full_size + line_len + 1 >= *full_capacity)
	{
		new_capacity = *full_capacity == 0 ? 1024 : *full_capacity * 2;
		new_input = ft_realloc(*full_input, new_capacity);
		if (!new_input)
			return (0);
		*full_input = new_input;
		*full_capacity = new_capacity;
	}
	ft_memcpy(*full_input + *full_size, line, line_len);
	*full_size += line_len;
	(*full_input)[*full_size] = '\0';
	return (1);
}

char	*read_heredoc_line(int is_piped)
{
	char	*line;

	if (is_piped)
		line = readline("> ");
	else
		line = readline("> ");
	if (!line)
		return (NULL);
	return (line);
}
