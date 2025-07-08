/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:10:15 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 21:05:25 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_key(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

int	env_count(char **e)
{
	int	i;

	i = 0;
	while (e && e[i])
		++i;
	return (i);
}

int	handle_export_arg(t_minishell *sh, char *arg)
{
	char	*eq;
	char	*key;
	int		ret;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = gc_strndup(sh, arg, eq - arg);
	else
		key = gc_strdup(sh, arg);
	if (!key)
		return (1);
	ret = 0;
	if (!is_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ret = 1;
	}
	else if (eq)
		ret = env_set(sh, arg);
	else
		ret = env_set(sh, key);
	return (ret);
}

void	sort_strings(char **arr)
{
	int		n;
	int		i;
	int		j;
	char	*tmp;

	n = env_count(arr);
	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
