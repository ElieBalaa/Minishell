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

static void	add_heredoc_delimiter(t_ast *node, char *delimiter)
{
	int		count;
	char	**new_delims;
	int		j;
	char	*clean_delim;

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
	clean_delim = remove_quotes(delimiter);
	new_delims[count] = clean_delim;
	new_delims[count + 1] = NULL;
	free(node->heredoc_delims);
	node->heredoc_delims = new_delims;
}

void	process_heredoc_redir(char **tok, int *i, t_ast *node)
{
	(*i)++;
	if (!node->heredoc_delims)
	{
		node->heredoc_delims = malloc(2 * sizeof(char *));
		node->heredoc_delims[0] = remove_quotes(tok[*i]);
		node->heredoc_delims[1] = NULL;
	}
	else
		add_heredoc_delimiter(node, tok[*i]);
	node->is_heredoc = 1;
}
