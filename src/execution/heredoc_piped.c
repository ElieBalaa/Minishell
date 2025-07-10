/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 19:11:16 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_originally_quoted(const char *delimiter)
{
	if (delimiter && delimiter[0] == '\'')
		return (1);
	return (0);
}

static int	handle_heredoc_line(t_delimiter_content_params *params,
		char *line, int is_quoted)
{
	if (!is_quoted)
	{
		if (!append_expanded_line(params->sh, line, params->vars))
			return (-1);
	}
	else
	{
		if (!append_raw_line(params->sh, line, params->vars))
			return (-1);
	}
	return (0);
}

static int	process_heredoc_content(t_delimiter_content_params *params,
		char *clean_delim, int is_quoted)
{
	char	*line;

	while (1)
	{
		if (!params->is_piped)
			heredoc_prompt();
		line = read_heredoc_line(params->is_piped);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, clean_delim))
		{
			free(line);
			break ;
		}
		if (params->is_last)
		{
			if (handle_heredoc_line(params, line, is_quoted) == -1)
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	return (0);
}

int	process_delimiter_content(t_delimiter_content_params *params)
{
	char	*clean_delim;
	int		is_quoted;

	is_quoted = is_originally_quoted(params->delimiter);
	if (is_quoted)
		clean_delim = ft_strdup(params->delimiter + 1);
	else
		clean_delim = ft_strdup(params->delimiter);
	if (process_heredoc_content(params, clean_delim, is_quoted) == -1)
	{
		free(clean_delim);
		return (-1);
	}
	free(clean_delim);
	return (0);
}
