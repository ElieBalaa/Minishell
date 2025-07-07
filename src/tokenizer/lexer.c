/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:18:34 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/03 17:13:46 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static void	add_tok(t_token **lst, t_minishell *sh, const char *start, int len)
{
	t_token	*node;
	char	*raw;
	char	*expd;
	char	*text;

	raw = process_token_escapes(gc_strndup(sh, start, len));
	expd = expand_vars(sh, raw);
	text = qc_remove_quotes(expd);
	free(raw);
	free(expd);
	node = malloc(sizeof(*node));
	if (!node)
		return (free(text));
	node->text = text;
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
		tok_last(*lst)->next = node;
}

static void	advance_word(const char **ptr)
{
	const char	*p;

	p = *ptr;
	while (*p && !is_space(*p) && !is_operator(*p))
	{
		if (*p == '\'' || *p == '"')
			p = skip_quotes(p);
		else if (*p == '\\' && p[1])
			p += 2;
		else
			p++;
	}
	*ptr = p;
}

static void	process_operator(t_token **lst, t_minishell *sh, const char **p)
{
	int	len;

	len = op_len(*p);
	add_tok(lst, sh, *p, len);
	*p += len;
}

static void	process_word(t_token **lst, t_minishell *sh, const char **p)
{
	const char	*start;
	int			len;

	start = *p;
	advance_word(p);
	len = (int)(*p - start);
	add_tok(lst, sh, start, len);
}

t_token	*tokenize(const char *line, t_minishell *sh)
{
	t_token		*lst;
	const char	*p;

	if (!line)
		return (NULL);
	lst = NULL;
	p = line;
	while (*p)
	{
		if (is_space(*p))
			p++;
		else if (is_operator(*p))
			process_operator(&lst, sh, &p);
		else
			process_word(&lst, sh, &p);
	}
	return (lst);
}
