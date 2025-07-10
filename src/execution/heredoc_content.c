/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 20:54:34 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_expanded_content(t_minishell *sh, char *line, int *pipe_fd)
{
	char	*expanded_line;

	expanded_line = expand_vars(sh, line);
	if (expanded_line)
	{
		write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
		write(pipe_fd[1], "\n", 1);
		free(expanded_line);
	}
	free(line);
	return (0);
}

static int	process_delimiter_loop(t_minishell *sh, char *delimiter,
		int *pipe_fd, void (*old_handler)(int))
{
	char	*line;

	while (1)
	{
		heredoc_prompt();
		line = read_heredoc_line(0);
		if (!line)
		{
			signal(SIGINT, old_handler);
			return (-1);
		}
		if (check_delimiter_match(line, delimiter))
		{
			free(line);
			break ;
		}
		if (write_expanded_content(sh, line, pipe_fd) == -1)
		{
			signal(SIGINT, old_handler);
			return (-1);
		}
	}
	return (0);
}

static int	process_single_delimiter(t_minishell *sh, char *delimiter,
		int *pipe_fd)
{
	void	(*old_handler)(int);
	int		ret;

	old_handler = signal(SIGINT, heredoc_sig_handler);
	ret = process_delimiter_loop(sh, delimiter, pipe_fd, old_handler);
	signal(SIGINT, old_handler);
	return (ret);
}

int	process_content(t_minishell *sh, char **delimiters, int *pipe_fd,
		char *full_input)
{
	int		i;

	(void)full_input;
	if (!sh || !delimiters || !pipe_fd)
		return (-1);
	i = 0;
	while (delimiters[i])
	{
		if (process_single_delimiter(sh, delimiters[i], pipe_fd) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	handle_heredoc_line(t_delimiter_content_params *params,
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
