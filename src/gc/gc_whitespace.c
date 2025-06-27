/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/07 00:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	count_words(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_whitespace(str[i]))
			in_word = 0;
		i++;
	}
	return (count);
}

char	*extract_word(char *str, int *start)
{
	int		end;
	char	*word;
	int		len;
	int		i;

	while (str[*start] && is_whitespace(str[*start]))
		(*start)++;
	if (!str[*start])
		return (NULL);
	end = *start;
	while (str[end] && !is_whitespace(str[end]))
		end++;
	len = end - *start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[*start + i];
		i++;
	}
	word[len] = '\0';
	*start = end;
	return (word);
}

static void	free_partial_words(char **words, int count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
}

char	**split_whitespace(char *str)
{
	char	**words;
	int		word_count;
	int		i;
	int		pos;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < word_count)
	{
		words[i] = extract_word(str, &pos);
		if (!words[i])
		{
			free_partial_words(words, i);
			return (NULL);
		}
		i++;
	}
	words[word_count] = NULL;
	return (words);
} 