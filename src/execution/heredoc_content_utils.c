/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_and_concat_content(t_minishell *sh, char **content,
		char **concatenated_content, size_t *total_size)
{
	char	*expanded_content;
	size_t	exp_len;
	size_t	capacity;

	expanded_content = expand_vars(sh, *content);
	exp_len = ft_strlen(expanded_content);
	capacity = *total_size + exp_len + 1024;
	if (*total_size + exp_len >= capacity)
	{
		capacity = capacity * 2;
		*concatenated_content = ft_realloc(*concatenated_content, capacity);
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

static int	process_helper(char **delimiters,
		int i, int last_index)
{
	char	*content;
	char	*current_pos;
	int		is_piped;

	content = NULL;
	current_pos = NULL;
	is_piped = !isatty(STDIN_FILENO);
	if (!is_piped)
	{
		if (process_piped_content(&content, &current_pos, delimiters[i]) == -1)
		{
			free(content);
			return (-1);
		}
	}
	else if (process_interactive_content(&content, delimiters[i],
			i == last_index, is_piped) == -1)
	{
		free(content);
		return (-1);
	}
	return (0);
}

static int	process_content_loop_inner(t_minishell *sh, char **delimiters,
		int last_index, char *full_input)
{
	int		i;
	char	*content;
	char	*concatenated_content;
	size_t	total_size;

	i = 0;
	content = NULL;
	concatenated_content = NULL;
	total_size = 0;
	while (delimiters[i])
	{
		if (process_helper(delimiters, i, last_index) == -1)
		{
			free(full_input);
			free(concatenated_content);
			return (-1);
		}
		if (content && i == last_index)
		{
			if (!expand_and_concat_content(sh, &content, &concatenated_content,
					&total_size))
			{
				free(content);
				return (-1);
			}
		}
		else if (content)
			free(content);
		i += 1;
	}
	return (0);
}

static int	process_content_logic(t_minishell *sh, char **delimiters,
		int last_index, char *full_input)
{
	return (process_content_loop_inner(sh, delimiters, last_index, full_input));
}

int	process_content_loop(t_minishell *sh, char **delimiters,
		int last_index, char *full_input)
{
	return (process_content_logic(sh, delimiters, last_index, full_input));
}
