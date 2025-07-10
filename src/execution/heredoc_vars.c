/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_heredoc_vars(char **delimiters, int *i, int *last_index,
		int *is_piped)
{
	*i = 0;
	*last_index = find_last_delimiter_index(delimiters);
	if (*last_index < 0)
		return (-1);
	*is_piped = !isatty(STDIN_FILENO);
	return (0);
}

int	process_delimiter_content(t_delimiter_content_params *params)
{
	char	*line;

	while (1)
	{
		if (!params->is_piped)
			heredoc_prompt();
		line = read_heredoc_line(params->is_piped);
		if (!line)
			return (-1);
		if (check_delimiter_match(line, params->delimiter))
		{
			free(line);
			break ;
		}
		if (params->is_last)
		{
			if (!append_expanded_line(params->sh, line, params->vars))
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	return (0);
}
