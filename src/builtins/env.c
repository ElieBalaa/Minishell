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

int	builtin_env(t_minishell *sh, char **av)
{
	size_t	i;

	(void)av;
	i = 0;
	while (sh->env && sh->env[i])
		printf("%s\n", sh->env[i++]);
	return (0);
}
