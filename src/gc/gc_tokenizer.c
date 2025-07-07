/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 23:02:02 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*create_token(t_minishell *sh, char *word)
{
	t_token	*tok;

	tok = gc_malloc(sh, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->text = gc_strdup(sh, word);
	tok->next = NULL;
	return (tok);
}

static int	validate_split_input(t_minishell *sh, char *str, int *count)
{
	if (!str || !sh)
		return (0);
	*count = count_words(str);
	return (*count > 0);
}

t_token	**gc_split_on_space(t_minishell *sh, char *str)
{
	int			count;
	char		**words;
	t_token		**tokens;
	int			idx;

	if (!validate_split_input(sh, str, &count))
		return (NULL);
	words = split_whitespace(str);
	if (!words)
		return (NULL);
	tokens = gc_malloc(sh, sizeof(t_token *) * (count + 1));
	if (!tokens)
		return (NULL);
	idx = 0;
	while (idx < count && words[idx])
	{
		tokens[idx] = create_token(sh, words[idx]);
		if (!tokens[idx])
			return (NULL);
		idx++;
	}
	tokens[idx] = NULL;
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

char	*qc_remove_quotes(const char *s)
{
	int		len;
	char	*out;
	int		i;
	int		j;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (len < 2)
		return (ft_strdup(s));
	if (!((s[0] == '"' && s[len - 1] == '"')
			|| (s[0] == '\'' && s[len - 1] == '\'')))
		return (ft_strdup(s));
	out = malloc(len - 1);
	if (!out)
		return (NULL);
	i = 1;
	j = 0;
	while (i < len - 1)
		out[j++] = s[i++];
	out[j] = '\0';
	return (out);
}
