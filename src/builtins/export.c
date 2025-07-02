/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:14 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 20:08:56 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_set(t_minishell *sh, const char *str)
{
	char	*equal;
	int		i;
	char	**new_env;

	equal = ft_strchr(str, '=');
	if (!sh || !str || !equal)
		return (1);
	i = -1;
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], str, equal - str + 1))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strdup(str);
			return (sh->env[i] ? 0 : 1);
		}
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	ft_memcpy(new_env, sh->env, sizeof(char *) * i);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(sh->env);
	sh->env = new_env;
	if (new_env[i])
		return (0);
	return (1);
}

static void	print_sorted_export(char **env)
{
	char	**copy;
	int		i;
	char	*eq;

	copy = env_copy(env);
	if (!copy)
		return ;
	sort_strings(copy);
	i = 0;
	while (copy[i])
	{
		eq = ft_strchr(copy[i], '=');
		if (eq)
		{
			printf("declare -x %.*s=\"%s\"\n",
				(int)(eq - copy[i]), copy[i], eq + 1);
		}
		else
			printf("declare -x %s\n", copy[i]);
		i++;
	}
	free(copy);
}

int	builtin_export(t_minishell *sh, char **av)
{
	int		i;
	int		err;
	char	*eq;
	char	*key;
	char	*value;

	if (!av[1])
	{
		print_sorted_export(sh->env);
		return (0);
	}
	err = 0;
	i = 1;
	while (av[i])
	{
		eq    = ft_strchr(av[i], '=');
		key   = eq
			? ft_strndup(av[i], eq - av[i])
			: ft_strdup(av[i]);
		value = eq
			? eq + 1
			: "";
		if (!is_valid_key(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = 1;
		}
		else
		{
			if (eq && env_set(sh, av[i]) != 0)
				err = 1;
			else if (setenv(key, value, 1) != 0)
			{
				perror("minishell: setenv");
				err = 1;
			}
		}
		free(key);
		i++;
	}
	return (err);
}
