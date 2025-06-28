/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:03:33 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 15:25:11 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**tok_to_array(t_token *lst)
{
	int			count;
	char		**arr;
	int			i;
	t_token		*tmp;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = gc_malloc(sizeof(*arr) * (count + 1));
	i = 0;
	tmp = lst;
	while (tmp)
	{
		arr[i++] = tmp->text;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_ast	*parse_line(const char *line)
{
	t_token	*tok;
	char	**words;
	t_ast	*root;

	tok = tokenize(line);
	words = tok_to_array(tok);
	root = parse_pipeline(words);
	return (root);
}

t_ast	*init_ast_node(void)
{
	t_ast	*node;

	node = gc_malloc(sizeof(*node));
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
