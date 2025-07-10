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

static int	is_quoted_delimiter(char *str)
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

static void	copy_existing_delims(char **new_delims, char **heredoc_delims, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		new_delims[j] = heredoc_delims[j];
		j++;
	}
}

static char	*prepare_quoted_delimiter(char *delimiter)
{
	char	*clean_delim;
	char	*quoted_marker;

	clean_delim = remove_quotes(delimiter);
	quoted_marker = ft_strjoin("'", clean_delim);
	free(clean_delim);
	return (quoted_marker);
}

static void	add_heredoc_delimiter(t_ast *node, char *delimiter)
{
	int		count;
	char	**new_delims;
	char	*clean_delim;
	int		is_quoted;

	count = 0;
	while (node->heredoc_delims[count])
		count++;
	new_delims = malloc((count + 2) * sizeof(char *));
	if (!new_delims)
		return ;
	copy_existing_delims(new_delims, node->heredoc_delims, count);
	is_quoted = is_quoted_delimiter(delimiter);
	if (is_quoted)
		clean_delim = prepare_quoted_delimiter(delimiter);
	else
		clean_delim = ft_strdup(delimiter);
	new_delims[count] = clean_delim;
	new_delims[count + 1] = NULL;
	free(node->heredoc_delims);
	node->heredoc_delims = new_delims;
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
