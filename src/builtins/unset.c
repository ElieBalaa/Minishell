/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:19 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 21:01:26 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset_env(t_minishell *sh, const char *key)
{
	int		old_len;
	int		i;
	int		j;
	char	**new_env;

	old_len = env_count(sh->env);
	new_env = malloc(sizeof(*new_env) * old_len);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (sh->env[i])
	{
		if (!(ft_strncmp(sh->env[i], key, ft_strlen(key)) == 0
				&& sh->env[i][ft_strlen(key)] == '='))
		{
			new_env[j++] = sh->env[i];
		}
		else
			free(sh->env[i]);
		++i;
	}
	new_env[j] = NULL;
	free(sh->env);
	sh->env = new_env;
}


int	builtin_unset(t_minishell *sh, char **args)
{
	int	i;
	int	err;

	err = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = 1;
		}
		else
			builtin_unset_env(sh, args[i]);
		++i;
	}
	return (err);
}
