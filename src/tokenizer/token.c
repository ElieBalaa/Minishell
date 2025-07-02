/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:29 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:26:42 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_argv(char **tokens, int n, char **argv, t_ast *node)
{
	int	i;
	int	j;
	int	max_args;

	max_args = count_args(tokens, n);
	i = -1;
	j = 0;
	while (++i < n && tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0)
			process_redir(tokens, &i, node);
		else if (j < max_args)
			argv[j++] = ft_strdup(tokens[i]);
	}
	argv[j] = NULL;
}

t_ast	*parse_segment(char **tokens, int n)
{
	t_ast	*node;
	char	**argv;

	node = init_ast_node();
	argv = malloc(sizeof(*argv) * (count_args(tokens, n) + 1));
	if (!argv)
		return (NULL);
	fill_argv(tokens, n, argv, node);
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

static t_ast	*create_segment_node(char **w, int start, int i)
{
	return (parse_segment(w + start,
			i - start + (ft_strcmp(w[i], "|") != 0)));
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
		if (is_pipeline_end(w, i))
		{
			node = create_segment_node(w, start, i);
			root = add_pipeline_node(root, cur, node);
			cur = node;
			start = i + 1;
		}
		i++;
	}
	return (root);
}
