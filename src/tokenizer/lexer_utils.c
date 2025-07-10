/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:45:00 by the-flash        #+#    #+#             */
/*   Updated: 2025/07/10 19:45:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_tok(t_token **lst, t_minishell *sh, const char *start, int len);

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