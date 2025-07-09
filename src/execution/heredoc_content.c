/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
int	process_piped_content(char **content, char **current_pos,
		char *delimiter, int is_last)
{
	char	*delim_pos;
	size_t	content_size;
	size_t	content_capacity;
	char	*line;

	delim_pos = *current_pos;
	content_size = 0;
	content_capacity = 0;
	*content = NULL;
	while (*delim_pos)
	{
		line = extract_line(current_pos);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			return (0);
		}
		if (is_last && !append_content_line(content, line, &content_size,
				&content_capacity))
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	process_interactive_content(char **content, char *delimiter,
		int is_last, int is_piped)
{
	*content = NULL;
	if (!is_piped)
		heredoc_prompt();
	return (handle_interactive_loop(content, delimiter, is_last, is_piped));
}
*/

static int	write_content_to_pipe(char *concatenated_content,
		size_t total_size, int *pipe_fd)
{
	if (concatenated_content)
	{
		write(pipe_fd[1], concatenated_content, total_size);
		free(concatenated_content);
	}
	return (0);
}

static int	expand_and_concat_content(t_minishell *sh, char **content,
		char **concatenated_content, size_t *total_size, size_t *capacity)
{
	char	*expanded_content;
	size_t	exp_len;

	expanded_content = expand_vars(sh, *content);
	exp_len = ft_strlen(expanded_content);
	if (*total_size + exp_len >= *capacity)
	{
		if (*capacity == 0)
			*capacity = 1024;
		else
			*capacity = *capacity * 2;
		*concatenated_content = ft_realloc(*concatenated_content, *capacity);
		if (!*concatenated_content)
		{
			free(expanded_content);
			return (0);
		}
	}
	ft_memcpy(*concatenated_content + *total_size, expanded_content, exp_len);
	*total_size += exp_len;
	(*concatenated_content)[*total_size] = '\0';
	free(*content);
	free(expanded_content);
	return (1);
}

static int	process_content_loop(t_minishell *sh, char **delimiters,
		int last_index, char *current_pos, char *full_input,
		char **concatenated_content, size_t *total_size, size_t *capacity)
{
	int		i;
	char	*content;

	i = 0;
	while (delimiters[i])
	{
		content = NULL;
		if (!isatty(STDIN_FILENO))
		{
			if (process_piped_content(&content, &current_pos, delimiters[i]) == -1)
			{
				free(content);
				free(full_input);
				free(*concatenated_content);
				return (-1);
			}
		}
		else if (process_interactive_content(&content, delimiters[i],
				i == last_index, !isatty(STDIN_FILENO)) == -1)
		{
			free(content);
			free(*concatenated_content);
			return (-1);
		}
		if (content)
		{
			if (!expand_and_concat_content(sh, &content, concatenated_content,
					total_size, capacity))
			{
				free(content);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	process_content(t_minishell *sh, char **delimiters, int *pipe_fd,
		char *full_input)
{
	int		last_index;
	char	*current_pos;
	char	*concatenated_content;
	size_t	total_size;
	size_t	capacity;

	last_index = find_last_delimiter_index(delimiters);
	current_pos = full_input;
	concatenated_content = NULL;
	total_size = 0;
	capacity = 0;
	if (process_content_loop(sh, delimiters, last_index, current_pos,
			full_input, &concatenated_content, &total_size, &capacity) == -1)
		return (-1);
	if (full_input)
		free(full_input);
	return (write_content_to_pipe(concatenated_content, total_size, pipe_fd));
}
