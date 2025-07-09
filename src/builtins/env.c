/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:31 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var(t_minishell *sh, const char *key)
{
	size_t	key_len;
	int		i;

	if (!sh || !key || !sh->env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], key, key_len) && sh->env[i][key_len] == '=')
			return (sh->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_env(t_minishell *sh, char **av)
{
	size_t	i;

	(void)av;
	i = 0;
	while (sh->env && sh->env[i])
		printf("%s\n", sh->env[i++]);
	return (0);
}

char	**env_copy(char **env)
{
	char	**copy;
	int		i;
	int		count;

	if (!env)
		return (NULL);
	count = env_count(env);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			free_env_strings(copy);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_env_strings(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
}
