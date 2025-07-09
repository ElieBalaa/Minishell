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

int	process_content(t_minishell *sh, char **delimiters, int *pipe_fd,
		char *full_input)
{
	int		i;
	char	*line;
	char	*expanded_line;

	(void)full_input;
	if (!sh || !delimiters || !pipe_fd)
		return (-1);
	i = 0;
	while (delimiters[i])
	{
		while (1)
		{
			heredoc_prompt();
			line = read_heredoc_line(0);
			if (!line)
				return (-1);
			if (check_delimiter_match(line, delimiters[i]))
			{
				free(line);
				break ;
			}
			expanded_line = expand_vars(sh, line);
			if (expanded_line)
			{
				write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
				write(pipe_fd[1], "\n", 1);
				free(expanded_line);
			}
			free(line);
		}
		i++;
	}
	return (0);
}
