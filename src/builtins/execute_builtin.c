/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:31:25 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 16:15:45 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_minishell *sh, char **args)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(sh, args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(sh, args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(sh, args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(sh, args));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(sh, args));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(sh, args));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(sh, args));
	return (-1);
}
