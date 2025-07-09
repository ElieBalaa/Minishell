/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:30:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/09 10:30:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lookup_env_var(t_minishell *sh, const char *name, int len)
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

char	*expand_one(t_minishell *sh, const char *p, int *adv)
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

char	*handle_dollar(t_minishell *sh, const char *s, size_t *i, char *res)
{
	int		adv;
	char	*val;
	char	*tmp;

	val = expand_one(sh, s + *i + 1, &adv);
	tmp = gc_strjoin(sh, res, val);
	*i += adv + 1;
	return (tmp);
}

char	*handle_char(t_minishell *sh, const char s, char *res)
{
	char	ch[2];
	char	*tmp;

	ch[0] = s;
	ch[1] = '\0';
	tmp = gc_strjoin(sh, res, ch);
	return (tmp);
}
