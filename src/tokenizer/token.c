/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:29 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 23:08:21 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_redirections(t_ast *node, char **tokens, int *i, int n)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && *i + 1 < n)
		node->input = strip_surrounding_quotes(tokens[++(*i)]);
	else if ((ft_strcmp(tokens[*i], ">") == 0
			|| ft_strcmp(tokens[*i], ">>") == 0) && *i + 1 < n)
		node->output = strip_surrounding_quotes(tokens[++(*i)]);
}

t_ast	*parse_segment(char **tokens, int n)
{
	t_ast	*node;
	char	**argv;
	int		i;
	int		j;

	node = gc_malloc(sizeof(*node));
	node->input = NULL;
	node->output = NULL;
	node->right = NULL;
	argv = gc_malloc(sizeof(*argv) * (count_args(tokens, n) + 1));
	if (!argv)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < n)
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0)
			handle_redirections(node, tokens, &i, n);
		else
			argv[j++] = strip_surrounding_quotes(tokens[i]);
	}
	argv[j] = NULL;
	node->cmd = argv;
	return (node);
}

t_ast	*add_pipeline_node(t_ast *root, t_ast *cur, t_ast *node)
{
	if (!root)
		root = node;
	else
		cur->right = node;
	return (root);
}

t_ast	*parse_pipeline(char **w)
{
	int		i;
	int		start;
	t_ast	*root;
	t_ast	*cur;
	t_ast	*node;

	i = 0;
	start = 0;
	root = NULL;
	cur = NULL;
	while (w[i])
	{
		if (ft_strcmp(w[i], "|") == 0 || w[i + 1] == NULL)
		{
			node = parse_segment(
					w + start,
					i - start + (ft_strcmp(w[i], "|") != 0));
			root = add_pipeline_node(root, cur, node);
			cur = node;
			start = i + 1;
		}
		i++;
	}
	return (root);
}
