/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/04 15:39:28 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

int	should_process_escape(char next_char, int in_single, int in_double)
{
	if (in_single)
		return (0);
	if (in_double)
		return (next_char == '"' || next_char == '\\' || next_char == '$');
	return (1);
}

static void	handle_quote_char(const char *str, int *i, int *j, char *result)
{
	result[(*j)++] = str[(*i)++];
}

static void	handle_escape_char(const char *str, int *i, int *j, char *result)
{
	result[(*j)++] = str[*i + 1];
	*i += 2;
}

static void	process_escape_loop(const char *str, int *i, int *j, char *result)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' && !in_double)
		{
			in_single = !in_single;
			handle_quote_char(str, i, j, result);
		}
		else if (str[*i] == '"' && !in_single)
		{
			in_double = !in_double;
			handle_quote_char(str, i, j, result);
		}
		else if (str[*i] == '\\' && str[*i + 1]
			&& should_process_escape(str[*i + 1], in_single, in_double))
			handle_escape_char(str, i, j, result);
		else
			result[(*j)++] = str[(*i)++];
	}
}

char	*process_token_escapes(const char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	result = gc_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	process_escape_loop(str, &i, &j, result);
	result[j] = '\0';
	return (result);
}
