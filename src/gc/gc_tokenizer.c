/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/27 18:09:40 by oiskanda         ###   ########.fr       */
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
