/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:05 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 15:20:37 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(t_minishell *sh, char **av)
{
	char	*dir;

	(void)sh;
	if (av[1])
		dir = av[1];
	else
		dir = getenv("HOME");
	if (!dir)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(dir) == -1)
		return (perror("minishell: cd"), 1);
	return (0);
}
