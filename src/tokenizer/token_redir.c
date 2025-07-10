/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:11:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:24:36 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_heredoc_delimiter(t_ast *node, char *delimiter)
{
	int		count;
	char	**new_delims;
	int		j;

	count = 0;
	while (node->heredoc_delims[count])
		count++;
	new_delims = malloc((count + 2) * sizeof(char *));
	if (!new_delims)
		return ;
	j = 0;
	while (j < count)
	{
		new_delims[j] = node->heredoc_delims[j];
		j++;
	}
	new_delims[count] = ft_strdup(delimiter);
	new_delims[count + 1] = NULL;
	free(node->heredoc_delims);
	node->heredoc_delims = new_delims;
}

static void	process_input_redir(char **tok, int *i, t_ast *node)
{
	(*i)++;
	node->input = ft_strdup(tok[*i]);
}

static void	process_heredoc_redir(char **tok, int *i, t_ast *node)
{
	(*i)++;
	if (!node->heredoc_delims)
	{
		node->heredoc_delims = malloc(2 * sizeof(char *));
		node->heredoc_delims[0] = ft_strdup(tok[*i]);
		node->heredoc_delims[1] = NULL;
	}
	else
		add_heredoc_delimiter(node, tok[*i]);
	node->is_heredoc = 1;
}

static void	process_output_redir(char **tok, int *i, t_ast *node)
{
	int	is_append;

	is_append = (ft_strcmp(tok[*i], ">>") == 0);
	(*i)++;
	node->output = ft_strdup(tok[*i]);
	if (is_append)
		node->append = 1;
}

void	process_redir(char **tok, int *i, t_ast *node)
{
	if (!tok || !tok[*i] || !node || *i < 0)
		return ;
	if (ft_strcmp(tok[*i], "<") == 0 && tok[*i + 1])
		process_input_redir(tok, i, node);
	else if (ft_strcmp(tok[*i], "<<") == 0 && tok[*i + 1])
		process_heredoc_redir(tok, i, node);
	else if ((ft_strcmp(tok[*i], ">") == 0
			|| ft_strcmp(tok[*i], ">>") == 0) && tok[*i + 1])
		process_output_redir(tok, i, node);
}
