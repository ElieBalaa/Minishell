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

static void	fill_segment_args(t_fill_args *args)
{
	int	i;
	int	arg_idx;

	i = 0;
	arg_idx = 0;
	while (i < args->n && ft_strcmp(args->tokens[i], "|"))
	{
		if (is_redir(args->tokens[i]))
			process_redir(args->tokens, &i, args->node);
		else
		{
			args->argv[arg_idx] = gc_strdup(args->sh, args->tokens[i]);
			arg_idx++;
		}
		i++;
	}
	args->argv[arg_idx] = NULL;
}

t_ast	*init_ast_node(t_minishell *sh)
{
	t_ast	*ast;

	ast = gc_malloc(sh, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->cmd = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->input = NULL;
	ast->output = NULL;
	ast->heredoc_delims = NULL;
	ast->append = 0;
	ast->is_heredoc = 0;
	return (ast);
}

t_ast	*parse_segment(char **tokens, int n, t_minishell *sh)
{
	t_ast		*node;
	char		**argv;
	int			argc;
	t_fill_args	args;

	node = init_ast_node(sh);
	if (!node)
		return (NULL);
	argc = count_args(tokens, n);
	if (argc == 0)
	{
		free(node);
		return (NULL);
	}
	argv = gc_malloc(sh, sizeof(*argv) * (argc + 1));
	if (!argv)
	{
		free(node);
		return (NULL);
	}
	args = (t_fill_args){tokens, n, argv, node, sh};
	fill_segment_args(&args);
	node->cmd = argv;
	return (node);
}

static void	process_pipeline_segment(t_pipeline_args *args,
	t_pipeline_ctx *ctx)
{
	int		is_not_pipe;
	int		count;

	is_not_pipe = (ft_strcmp(args->w[args->i], "|") != 0);
	count = args->i - args->start + is_not_pipe;
	if (!*(ctx->root))
	{
		*(ctx->root) = parse_segment(args->w + args->start, count, args->sh);
		*(ctx->cur) = *(ctx->root);
	}
	else
	{
		(*(ctx->cur))->right = parse_segment(args->w + args->start,
				count, args->sh);
		*(ctx->cur) = (*(ctx->cur))->right;
	}
}

t_ast	*parse_pipeline(char **w, t_minishell *sh)
{
	int				i;
	int				start;
	t_ast			*root;
	t_pipeline_ctx	ctx;
	t_pipeline_args	args;

	i = 0;
	start = 0;
	root = NULL;
	ctx.root = &root;
	ctx.cur = &root;
	while (w[i])
	{
		if (is_pipeline_end(w, i))
		{
			args = (t_pipeline_args){w, start, i, sh};
			process_pipeline_segment(&args, &ctx);
			start = i + 1;
		}
		i++;
	}
	return (root);
}
