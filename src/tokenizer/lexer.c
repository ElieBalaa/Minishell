/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:18:34 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 20:04:10 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static int	check_heredoc_delimiter(t_token **lst)
{
	t_token	*last;

	if (!*lst)
		return (0);
	last = tok_last(*lst);
	if (last && ft_strcmp(last->text, "<<") == 0)
		return (1);
	return (0);
}

static char	*process_heredoc_token(t_minishell *sh, const char *start, int len)
{
	char	*raw;
	char	*expd;

	raw = process_token_escapes(sh, gc_strndup(sh, start, len));
	if (len >= 2 && ((start[0] == '\'' && start[len - 1] == '\'')
			|| (start[0] == '"' && start[len - 1] == '"')))
		return (process_quoted_delimiter(sh, start, len));
	expd = expand_vars(sh, raw);
	return (expd);
}

static char	*process_regular_token(t_minishell *sh, const char *start, int len)
{
	char	*raw;
	char	*expd;

	raw = process_token_escapes(sh, gc_strndup(sh, start, len));
	expd = expand_vars(sh, raw);
	return (expd);
}

void	add_tok(t_token **lst, t_minishell *sh, const char *start, int len)
{
	t_token	*node;
	char	*text;
	int		is_heredoc_delim;

	is_heredoc_delim = check_heredoc_delimiter(lst);
	if (is_heredoc_delim)
		text = process_heredoc_token(sh, start, len);
	else
		text = process_regular_token(sh, start, len);
	node = gc_malloc(sh, sizeof(*node));
	node->text = text;
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
		tok_last(*lst)->next = node;
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
