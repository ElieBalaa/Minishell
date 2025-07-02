/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:18:34 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 14:13:02 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static void	add_tok(t_token **lst, const char *start, int len, int last_exit)
{
	t_token	*node;
	char	*tmp;
	char	*text;

	tmp = gc_strndup(start, len);
	if (!tmp)
		return ;
	tmp = process_token_escapes(tmp);
	if (!tmp)
		return ;
	tmp = expand_vars(tmp, last_exit);
	if (!tmp)
		return ;
	tmp = qc_remove_quotes(tmp);
	if (!tmp)
		return ;
	text = gc_strdup(tmp);
	if (!text)
		return ;
	node = malloc(sizeof(*node));
	if (!node)
		return (free(text));
	node->text = text;
	node->next = NULL;
	if (*lst == NULL)
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

static void	process_operator(t_token **lst, const char **p, int last_exit)
{
	add_tok(lst, *p, op_len(*p), last_exit);
	*p += op_len(*p);
}

static void	process_word(t_token **lst, const char **p, int last_exit)
{
	const char	*start;

	start = *p;
	advance_word(p);
	add_tok(lst, start, *p - start, last_exit);
}

t_token	*tokenize(const char *line, int last_exit)
{
	t_token		*lst;
	const char	*p;

	lst = NULL;
	if (!line)
		return (NULL);
	p = line;
	while (*p)
	{
		if (is_space(*p))
		{
			p++;
			continue ;
		}
		if (is_operator(*p))
			process_operator(&lst, &p, last_exit);
		else
			process_word(&lst, &p, last_exit);
	}
	return (lst);
}
