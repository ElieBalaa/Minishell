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

static char	*lookup_env_var(t_minishell *sh, const char *p, int len)
{
	char	*val;
	int		i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], p, len) && sh->env[i][len] == '=')
		{
			val = ft_strdup(sh->env[i] + len + 1);
			return (val);
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*expand_one(t_minishell *sh, const char *p, int *adv)
{
	int		len;
	char	*s;

	if (*p == '?')
	{
		*adv = 1;
		s = ft_itoa(sh->last_exit);
		return (gc_add(sh, s), s);
	}
	if (!ft_isalpha(*p) && *p != '_')
	{
		*adv = 0;
		return (gc_strdup(sh, "$"));
	}
	len = 1;
	while (p[len] && (ft_isalnum(p[len]) || p[len] == '_'))
		len++;
	*adv = len;
	return (lookup_env_var(sh, p, len));
}

static char	*handle_var_expansion(t_minishell *sh, const char *s,
	size_t *i, char *result)
{
	char	*tmp;
	char	*new_result;
	int		adv;

	tmp = expand_one(sh, s + *i + 1, &adv);
	if (tmp)
	{
		new_result = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		result = new_result;
	}
	*i += adv + 1;
	return (result);
}

static char	*process_char(t_expand_ctx *ctx, char *result)
{
	char	*tmp;
	char	ch_str[2];

	if (ctx->s[*(ctx->i)] == '"' && !ctx->q[0])
	{
		ctx->q[1] ^= 1;
		tmp = ft_strjoin(result, "\"");
	}
	else if (ctx->s[*(ctx->i)] == '\'' && !ctx->q[1])
	{
		ctx->q[0] ^= 1;
		tmp = ft_strjoin(result, "\'");
	}
	else if (ctx->s[*(ctx->i)] == '$' && !ctx->q[0])
		return (handle_var_expansion(ctx->sh, ctx->s, ctx->i, result));
	else
	{
		ch_str[0] = ctx->s[*(ctx->i)];
		ch_str[1] = 0;
		tmp = ft_strjoin(result, ch_str);
	}
	free(result);
	return (tmp);
}

char	*expand_vars(t_minishell *sh, const char *s)
{
	size_t			i;
	int				q[2];
	char			*result;
	t_expand_ctx	ctx;

	if (!sh || !s)
		return (NULL);
	result = ft_strdup("");
	q[0] = 0;
	q[1] = 0;
	i = 0;
	ctx = (t_expand_ctx){sh, s, &i, q};
	while (s[i])
	{
		result = process_char(&ctx, result);
		if (s[i] != '$' || q[0])
			i++;
	}
	return (result);
}
