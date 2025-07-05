/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:54 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/04 22:09:05 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	var_length(const char *s)
{
	int	len;

	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	len = 1;
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	return (len);
}

static char	*lookup_var(const char *name, char **env)
{
	size_t	n;
	int		i;

	n = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, n) && env[i][n] == '=')
			return (gc_strdup(env[i] + n + 1));
		i++;
	}
	return (gc_strdup(""));
}

static char	*expand_one(const char *p, int *adv, int last_exit, char **env)
{
	char	*val;

	if (*p == '?')
	{
		*adv = 1;
		return (gc_itoa(last_exit));
	}
	*adv = var_length(p);
	if (*adv == 0)
		return (gc_strdup("$"));
	val = lookup_var(ft_strndup(p, *adv), env);
	return (val);
}

char	*expand_vars(const char *s, int last_exit, char **env)
{
	size_t	i;
	int		q[2];
	int		adv;
	char	*tmp;
	char	*result;

	result = gc_strdup("");
	q[0] = 0;
	q[1] = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !q[0])
		{
			q[1] ^= 1;
			result = gc_strjoin(result, "\"");
			i++;
		}
		else if (s[i] == '\'' && !q[1])
		{
			q[0] ^= 1;
			result = gc_strjoin(result, "\'");
			i++;
		}
		else if (s[i] == '$' && !q[0])
		{
			tmp = expand_one(s + i + 1, &adv, last_exit, env);
			result = gc_strjoin(result, tmp);
			i += adv + 1;
		}
		else
			result = gc_strjoin(result, gc_strndup(s + i++, 1));
	}
	return (result);
}
