/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:30:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/02 14:30:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = exit_code % 256;
	}
	printf("exit\n");
	exit(exit_code);
	return (exit_code);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_cd(char **args)
{
	char	*path;

	if (!args[1])
		path = getenv("HOME");
	else
		path = args[1];
	if (!path)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	builtin_pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	builtin_env(char **args)
{
	int	i;

	(void)args;
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
