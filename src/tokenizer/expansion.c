/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:54 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/10 18:51:40 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_quotes(const char *s, size_t *i, int *in_s, int *in_d)
{
	if (s[*i] == '\'' && !*in_d)
		*in_s ^= 1;
	else if (s[*i] == '"' && !*in_s)
		*in_d ^= 1;
	(*i)++;
}

static char	*process_expansion_loop(t_minishell *sh, const char *s, char *res)
{
	size_t	i;
	int		in_s;
	int		in_d;

	in_s = 0;
	in_d = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' && !in_d) || (s[i] == '"' && !in_s))
			handle_quotes(s, &i, &in_s, &in_d);
		else if (s[i] == '$' && !in_s)
			res = handle_dollar(sh, s, &i, res);
		else
		{
			res = handle_char(sh, s[i], res);
			i++;
		}
	}
	return (res);
}

char	*expand_vars(t_minishell *sh, const char *s)
{
	char	*res;

	if (!sh || !s)
		return (NULL);
	res = gc_strdup(sh, "");
	if (!res)
		return (NULL);
	res = process_expansion_loop(sh, s, res);
	return (res);
}
