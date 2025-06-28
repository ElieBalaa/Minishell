/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:18:34 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 19:23:51 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_tok(t_token **lst, const char *start, int len)
{
	t_token	*new;
	char	*txt;
	int		i;

	txt = gc_malloc(len + 1);
	i = 0;
	while (i < len)
	{
		txt[i] = start[i];
		i++;
	}
	txt[i] = '\0';
	new = gc_malloc(sizeof(*new));
	new->text = txt;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
		tok_last(*lst)->next = new;
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

static void	process_operator(t_token **lst, const char **p)
{
	add_tok(lst, *p, op_len(*p));
	*p += op_len(*p);
}

static void	process_word(t_token **lst, const char **p)
{
	const char	*start;

	start = *p;
	advance_word(p);
	add_tok(lst, start, *p - start);
}

t_token	*tokenize(const char *line)
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
			process_operator(&lst, &p);
		else
			process_word(&lst, &p);
	}
	return (lst);
}
