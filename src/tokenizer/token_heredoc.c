/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:11:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:24:36 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *str)
{
	int		len;

	if (!str || !str[0])
		return (ft_strdup(str));
	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
		return (ft_strndup(str + 1, len - 2));
	return (ft_strdup(str));
}

int	is_quoted_delimiter(char *str)
{
	int	len;

	if (!str || !str[0])
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
		return (1);
	return (0);
}

void	process_heredoc_redir(char **tok, int *i, t_ast *node)
{
	char	*clean_delim;

	(*i)++;
	if (!node->heredoc_delims)
	{
		node->heredoc_delims = malloc(2 * sizeof(char *));
		if (is_quoted_delimiter(tok[*i]))
		{
			clean_delim = remove_quotes(tok[*i]);
			node->heredoc_delims[0] = ft_strjoin("'", clean_delim);
			free(clean_delim);
		}
		else
			node->heredoc_delims[0] = ft_strdup(tok[*i]);
		node->heredoc_delims[1] = NULL;
	}
	else
		add_heredoc_delimiter(node, tok[*i]);
	node->is_heredoc = 1;
}
