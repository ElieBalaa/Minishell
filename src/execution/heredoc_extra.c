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

int	append_line_to_input(t_input_vars *vars, char *line)
{
	size_t	line_len;
	size_t	new_capacity;
	char	*new_input;

	line_len = ft_strlen(line);
	if (vars->size + line_len + 1 >= vars->capacity)
	{
		if (vars->capacity == 0)
			new_capacity = 1024;
		else
			new_capacity = vars->capacity * 2;
		new_input = ft_realloc(vars->input, new_capacity);
		if (!new_input)
			return (0);
		vars->input = new_input;
		vars->capacity = new_capacity;
	}
	ft_memcpy(vars->input + vars->size, line, line_len);
	vars->size += line_len;
	vars->input[vars->size] = '\0';
	return (1);
}

char	*read_heredoc_line(int is_piped)
{
	char	*line;
	size_t	len;
	ssize_t	read_result;

	if (is_piped)
	{
		line = NULL;
		len = 0;
		read_result = getline(&line, &len, stdin);
		if (read_result == -1)
		{
			free(line);
			return (NULL);
		}
		if (line && line[read_result - 1] == '\n')
			line[read_result - 1] = '\0';
		return (line);
	}
	else
	{
		line = readline("");
		if (!line)
			return (NULL);
		return (line);
	}
}

int	process_loop_line(t_delimiter_content_params *params,
		char *line, char *clean_delim, int is_quoted)
{
	if (check_delimiter_match(line, clean_delim))
	{
		free(line);
		return (1);
	}
	if (params->is_last && handle_heredoc_line(params, line, is_quoted) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}
