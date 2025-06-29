/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:45:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/02 14:45:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(char **args)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args));
	return (-1);
} 