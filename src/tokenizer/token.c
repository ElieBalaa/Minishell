/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:44:21 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/30 21:30:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_segment_args(char **tokens, int n, char **argv, t_ast *node)
{
	int	i;
	int	arg_idx;

	i = 0;
	arg_idx = 0;
	while (i < n && ft_strcmp(tokens[i], "|"))
	{
		if (is_redir(tokens[i]))
			process_redir(tokens, &i, node);
		else
		{
			argv[arg_idx] = ft_strdup(tokens[i]);
			arg_idx++;
		}
		i++;
	}
	argv[arg_idx] = NULL;
}

t_ast	*parse_segment(char **tokens, int n)
{
	t_ast	*node;
	char	**argv;
	int		argc;

	node = init_ast_node();
	if (!node)
		return (NULL);
	argc = count_args(tokens, n);
	if (argc == 0)
	{
		free(node);
		return (NULL);
	}
	argv = malloc(sizeof(*argv) * (argc + 1));
	if (!argv)
	{
		free(node);
		return (NULL);
	}
	fill_segment_args(tokens, n, argv, node);
	node->cmd = argv;
	return (node);
}

t_ast	*init_ast_node(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->cmd = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->input = NULL;
	ast->output = NULL;
	ast->heredoc_delim = NULL;
	ast->append = 0;
	ast->is_heredoc = 0;
	return (ast);
}

static void	process_pipeline_segment(char **w, int start, int i,
	t_pipeline_ctx *ctx)
{
	int		is_not_pipe;
	int		count;

	is_not_pipe = (ft_strcmp(w[i], "|") != 0);
	count = i - start + is_not_pipe;
	if (!*(ctx->root))
	{
		*(ctx->root) = parse_segment(w + start, count);
		*(ctx->cur) = *(ctx->root);
	}
	else
	{
		(*(ctx->cur))->right = parse_segment(w + start, count);
		*(ctx->cur) = (*(ctx->cur))->right;
	}
}

t_ast	*parse_pipeline(char **w)
{
	int				i;
	int				start;
	t_ast			*root;
	t_ast			*cur;
	t_pipeline_ctx	ctx;

	i = 0;
	start = 0;
	root = NULL;
	cur = NULL;
	ctx.root = &root;
	ctx.cur = &cur;
	while (w[i])
	{
		if (is_pipeline_end(w, i))
		{
			process_pipeline_segment(w, start, i, &ctx);
			start = i + 1;
		}
		i++;
	}
	return (root);
}
