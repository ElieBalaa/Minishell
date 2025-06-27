/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:29 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 00:45:47 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	**split_on_space(char *str)
{
	int		i;
	t_token	*tok;
	char	**words;
	t_token	**tokens;

	if (!str)
		return (NULL);
	words = ft_split_charset(str, " 	");
	tokens = (t_token **)malloc(sizeof(t_token *)
			* (count_double_array(words) + 1));
	if (!words || !tokens)
		return (NULL);
	i = -1;
	while (++i < count_double_array(words))
	{
		tok = (t_token *)malloc(sizeof(t_token));
		if (!tok)
			ft_putstr_fd("malloc failed", 2);
		tok->text = ft_strdup(words[i]);
		tok->next = NULL;
		tokens[i] = tok;
	}
	tokens[count_double_array(words)] = NULL;
	ft_free_split(words);
	return (tokens);
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

static void	fill_io(char **tok, int n, t_ast *node, char **av)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < n)
	{
		if (is_redir(tok[i]) && i + 1 < n)
		{
			if (ft_strcmp(tok[i], "<") == 0)
				node->input = ft_strdup(tok[++i]);
			else
			{
				node->append = (ft_strcmp(tok[i], ">>") == 0);
				node->output = ft_strdup(tok[++i]);
			}
		}
		else
			av[j++] = ft_strdup(tok[i]);
	}
	av[j] = NULL;
}

t_ast	*parse_segment(char **tokens, int n)
{
	t_ast	*node;
	char	**argv;
	int		argc;

	argc = count_args(tokens, n);
	argv = malloc(sizeof(*argv) * (argc + 1));
	node = malloc(sizeof(*node));
	node->input = NULL;
	node->output = NULL;
	node->right = NULL;
	node->append = 0;
	fill_io(tokens, n, node, argv);
	node->cmd = argv;
	return (node);
}
