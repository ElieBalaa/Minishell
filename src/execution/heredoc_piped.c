/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 20:54:43 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_piped_loop(t_delimiter_content_params *params,
		char *clean_delim, int is_quoted, void (*old_handler)(int))
{
	char	*line;
	int		result;

	while (1)
	{
		if (read_loop_line(params, &line, old_handler) == -1)
			return (-1);
		result = process_loop_line(params, line, clean_delim, is_quoted);
		if (result == 1)
			return (0);
		if (result == -1)
		{
			signal(SIGINT, old_handler);
			return (-1);
		}
	}
	return (0);
}

static int	process_heredoc_content(t_delimiter_content_params *params,
		char *clean_delim, int is_quoted)
{
	void	(*old_handler)(int);
	int		ret;

	old_handler = signal(SIGINT, heredoc_sig_handler);
	ret = heredoc_piped_loop(params, clean_delim, is_quoted, old_handler);
	signal(SIGINT, old_handler);
	return (ret);
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
