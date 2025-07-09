/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:11:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:24:36 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	op_len(const char *s)
{
	if (!s)
		return (0);
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	if (s[0] == '<' || s[0] == '>' || s[0] == '|')
		return (1);
	return (0);
}

t_token	*tok_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	process_redir(char **tok, int *i, t_ast *node)
{
	int	count;

	if (!tok || !tok[*i] || !node || *i < 0)
		return ;
	if (ft_strcmp(tok[*i], "<") == 0 && tok[*i + 1])
	{
		(*i)++;
		node->input = ft_strdup(tok[*i]);
	}
	else if (ft_strcmp(tok[*i], "<<") == 0 && tok[*i + 1])
	{
		(*i)++;
		if (!node->heredoc_delims)
		{
			node->heredoc_delims = malloc(2 * sizeof(char *));
			node->heredoc_delims[0] = ft_strdup(tok[*i]);
			node->heredoc_delims[1] = NULL;
		}
		else
		{
			count = 0;
			while (node->heredoc_delims[count])
				count++;
			node->heredoc_delims = ft_realloc(node->heredoc_delims,
					(count + 2) * sizeof(char *));
			node->heredoc_delims[count] = ft_strdup(tok[*i]);
			node->heredoc_delims[count + 1] = NULL;
		}
		node->is_heredoc = 1;
	}
	else if ((ft_strcmp(tok[*i], ">") == 0
			|| ft_strcmp(tok[*i], ">>") == 0) && tok[*i + 1])
	{
		(*i)++;
		node->output = ft_strdup(tok[*i]);
		if (ft_strcmp(tok[*i - 1], ">>") == 0)
			node->append = 1;
	}
}
