/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	resize_content_buffer(t_content_vars *vars)
{
	size_t	new_capacity;
	char	*new_content;

	if (vars->capacity == 0)
		new_capacity = 1024;
	else
		new_capacity = vars->capacity * 2;
	new_content = ft_realloc(vars->content, new_capacity);
	if (!new_content)
		return (0);
	vars->content = new_content;
	vars->capacity = new_capacity;
	return (1);
}

int	append_expanded_line(t_minishell *sh, char *line, t_content_vars *vars)
{
	char	*expanded_line;
	char	*content_to_write;

	if (!line)
		return (0);
	expanded_line = expand_vars(sh, line);
	if (!expanded_line)
		return (0);
	content_to_write = expanded_line;
	if (vars->size + ft_strlen(content_to_write) + 2 >= vars->capacity)
	{
		if (!resize_content_buffer(vars))
		{
			free(expanded_line);
			return (0);
		}
	}
	ft_memcpy(vars->content + vars->size, content_to_write,
		ft_strlen(content_to_write));
	vars->size += ft_strlen(content_to_write);
	vars->content[vars->size] = '\n';
	vars->size++;
	vars->content[vars->size] = '\0';
	free(expanded_line);
	return (1);
}

int	append_raw_line(t_minishell *sh, char *line, t_content_vars *vars)
{
	(void)sh;
	if (!line)
		return (0);
	if (vars->size + ft_strlen(line) + 2 >= vars->capacity)
	{
		if (!resize_content_buffer(vars))
			return (0);
	}
	ft_memcpy(vars->content + vars->size, line, ft_strlen(line));
	vars->size += ft_strlen(line);
	vars->content[vars->size] = '\n';
	vars->size++;
	vars->content[vars->size] = '\0';
	return (1);
}

void	init_content_vars(t_content_vars *vars)
{
	vars->content = NULL;
	vars->size = 0;
	vars->capacity = 0;
}

int	expand_and_concat_content(t_minishell *sh, char **content,
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
