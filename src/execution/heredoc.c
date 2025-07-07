/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_prompt(void)
{
	write(STDOUT_FILENO, "heredoc> ", 9);
}

static int	is_delimiter_match(char *buf, char *delim, size_t delim_len)
{
	size_t	buf_len;

	if (!buf || !delim)
		return (0);
	buf_len = ft_strlen(buf);
	if (buf_len > 0 && buf[buf_len - 1] == '\n')
		buf_len--;
	return (buf_len == delim_len && ft_strncmp(buf, delim, delim_len) == 0);
}

static int	read_heredoc_line(char *buf)
{
	char	c;
	size_t	i;

	if (!buf)
		return (0);
	i = 0;
	while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n' && i < 1023)
		buf[i++] = c;
	if (c == '\n')
		buf[i++] = '\n';
	buf[i] = '\0';
	return (i);
}

int	process_heredoc(t_minishell *sh, char *delimiter)
{
	int		pipe_fd[2];
	char	*buf;
	size_t	delim_len;
	int		bytes_read;

	if (!sh || !delimiter || pipe(pipe_fd) == -1)
		return (-1);
	buf = gc_malloc(sh, 1024);
	if (!buf)
		return (-1);
	delim_len = ft_strlen(delimiter);
	while (1)
	{
		heredoc_prompt();
		bytes_read = read_heredoc_line(buf);
		if (is_delimiter_match(buf, delimiter, delim_len))
			break ;
		write(pipe_fd[1], buf, bytes_read);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
