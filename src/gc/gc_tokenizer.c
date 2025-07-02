/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:39:55 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*create_token(char *word)
{
	t_token	*tok;

	tok = gc_malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->text = gc_strdup(word);
	if (!tok->text)
		return (NULL);
	tok->next = NULL;
	return (tok);
}

t_token	**gc_split_on_space(char *str)
{
	char	**words;
	t_token	**tokens;
	int		count;
	int		i;

	if (!str)
		return (NULL);
	words = split_whitespace(str);
	if (!words)
		return (NULL);
	count = count_double_array(words);
	tokens = gc_malloc(sizeof(t_token *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tokens[i] = create_token(words[i]);
		if (!tokens[i])
			return (NULL);
		i++;
	}
	tokens[count] = NULL;
	ft_free_split(words);
	return (tokens);
}

int	ft_tokensize(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	*gc_itoa(int n)
{
	char	*s;

	s = ft_itoa(n);
	return (gc_add(s), s);
}

char	*qc_remove_quotes(const char *s)
{
	size_t	i;
	size_t	w;
	char	quote;
	char	*out;

	if (!s)
		return (NULL);
	out = gc_malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	w = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && quote == 0)
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else
			out[w++] = s[i];
		++i;
	}
	out[w] = '\0';
	return (out);
}
