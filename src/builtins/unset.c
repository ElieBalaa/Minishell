/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:19 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 18:45:53 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_unset(t_minishell *sh, const char *key)
{
	int		old;
	int		i;
	int		j;
	char	**new;

	old = env_count(sh->env);
	new = gc_malloc(sh, sizeof(*new) * old);
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (sh->env[i])
	{
		if (!(ft_strncmp(sh->env[i], key, ft_strlen(key)) == 0
				&& sh->env[i][ft_strlen(key)] == '='))
			new[j++] = sh->env[i];
		else
			free(sh->env[i]);
		i++;
	}
	new[j] = NULL;
	free(sh->env);
	sh->env = new;
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
			env_unset(sh, args[i]);
		i++;
	}
	return (err);
}
