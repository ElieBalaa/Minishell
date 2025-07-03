/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:03:33 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/03 17:28:44 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **tok_to_array(t_token *lst)
{
	size_t	count;
	size_t	i;
	char	**arr;

	count = ft_tokensize(lst);
	arr = gc_malloc(sizeof(*arr) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i] = ft_strdup(lst->text);
		if (!arr[i])
		{
			while (i--)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		++i;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_ast	*parse_line(const char *line, t_minishell *sh)
{
	t_token	*tok;
	char	**words;
	t_ast	*root;

	tok = tokenize(line, sh);
	if (!tok)
		return (NULL);
	words = tok_to_array(tok);
	if (!words)
		return (NULL);
	root = parse_pipeline(words);
	return (root);
}

t_ast	*init_ast_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->input = NULL;
	node->output = NULL;
	node->append = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	is_pipeline_end(char **w, int i)
{
	return (ft_strcmp(w[i], "|") == 0 || w[i + 1] == NULL);
}

const char	*skip_quotes(const char *p)
{
	char	q;

	q = *p++;
	while (*p && *p != q)
	{
		if (q == '"' && *p == '\\' && p[1])
			p += 2;
		else
			p++;
	}
	if (*p == q)
		p++;
	return (p);
}
