/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 20:54:21 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_heredoc_iteration_struct(t_iteration_args *args)
{
	if (check_delimiter_match(args->line, args->clean_delim))
	{
		free(args->line);
		free(args->clean_delim);
		return (1);
	}
	if (process_heredoc_line(args->sh, args->line, args->pipe_fd,
			args->is_quoted) == -1)
		return (-1);
	return (0);
}

static int	process_loop_iteration(t_heredoc_args *args, char *clean_delim,
		int is_quoted, void (*old_handler)(int))
{
	char				*line;
	t_iteration_args	iter_args;
	t_setup_args		setup;

	if (!args->is_piped)
		heredoc_prompt();
	line = read_heredoc_line(args->is_piped);
	if (!line)
	{
		free(clean_delim);
		signal(SIGINT, old_handler);
		return (-1);
	}
	setup.args = args;
	setup.line = line;
	setup.clean_delim = clean_delim;
	setup.is_quoted = is_quoted;
	setup_iteration_args(&setup, &iter_args);
	if (handle_heredoc_iteration_struct(&iter_args) != 0)
	{
		signal(SIGINT, old_handler);
		return (-1);
	}
	return (0);
}

static int	heredoc_loop_body(t_heredoc_args *args, char *clean_delim,
		int is_quoted, void (*old_handler)(int))
{
	while (1)
	{
		if (process_loop_iteration(args, clean_delim, is_quoted,
				old_handler) != 0)
			return (-1);
	}
	return (0);
}

int	handle_heredoc_loop_struct(t_heredoc_args *args)
{
	int		is_quoted;
	char	*clean_delim;
	void	(*old_handler)(int);

	if (!args || !args->sh || !args->delimiter || !args->pipe_fd)
		return (-1);
	is_quoted = is_delimiter_quoted(args->delimiter);
	clean_delim = remove_quotes(args->delimiter);
	old_handler = signal(SIGINT, heredoc_sig_handler);
	if (heredoc_loop_body(args, clean_delim, is_quoted, old_handler) == -1)
		return (-1);
	signal(SIGINT, old_handler);
	return (0);
}

int	handle_heredoc_loop(t_minishell *sh, char *delimiter,
		int *pipe_fd, int is_piped)
{
	t_heredoc_args	args;

	args.sh = sh;
	args.delimiter = delimiter;
	args.pipe_fd = pipe_fd;
	args.is_piped = is_piped;
	return (handle_heredoc_loop_struct(&args));
}
