/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:54 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 21:03:09 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lookup_env_var(t_minishell *sh, const char *name, int len)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], name, len)
			&& sh->env[i][len] == '=')
			return (gc_strdup(sh, sh->env[i] + len + 1));
		i++;
	}
	return (gc_strdup(sh, ""));
}

static char	*expand_one(t_minishell *sh, const char *p, int *adv)
{
	char	*val;

	if (*p == '?')
	{
		*adv = 1;
		return (ft_itoa(sh->last_exit));
	}
	if (!ft_isalpha(*p) && *p != '_')
	{
		*adv = 0;
		return (gc_strdup(sh, "$"));
	}
	*adv = 1;
	while (p[*adv] && (ft_isalnum(p[*adv]) || p[*adv] == '_'))
		(*adv)++;
	val = lookup_env_var(sh, p, *adv);
	return (val);
}

char	*expand_vars(t_minishell *sh, const char *s)
{
	size_t	i;
	int		in_s;
	int		in_d;
	char	*res;

	if (!sh || !s)
		return (NULL);
	res = gc_strdup(sh, "");
	if (!res)
		return (NULL);
	in_s = in_d = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_d)
		{
			in_s ^= 1;
			i++;
		}
		else if (s[i] == '"' && !in_s)
		{
			in_d ^= 1;
			i++;
		}
		else if (s[i] == '$' && !in_s)
		{
			int	adv;
			char	*val = expand_one(sh, s + i + 1, &adv);
			char	*tmp = gc_strjoin(sh, res, val);
			res = tmp;
			i += adv + 1;
		}
		else
		{
			char	ch[2] = {s[i], '\0'};
			char	*tmp = gc_strjoin(sh, res, ch);
			// free(res);
			res = tmp;
			i++;
		}
	}
	return (res);
}