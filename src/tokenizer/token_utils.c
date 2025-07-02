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
	if ((s[0] == '<' || s[0] == '>') && s[1] == s[0])
		return (2);
	return (1);
}

t_token	*tok_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	process_redir(char **tok, int *i, t_ast *node)
{
	if (!tok || !tok[*i] || !node || *i < 0)
		return ;
	if (ft_strcmp(tok[*i], "<") == 0 && tok[*i + 1])
	{
		(*i)++;
		node->input = ft_strdup(tok[*i]);
	}
	else if ((ft_strcmp(tok[*i], ">") == 0
			|| ft_strcmp(tok[*i], ">>") == 0) && tok[*i + 1])
	{
		(*i)++;
		node->output = ft_strdup(tok[*i]);
	}
}
