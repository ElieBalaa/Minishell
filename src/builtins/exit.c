/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:12 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 16:47:52 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	count_exit_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static void	handle_exit_error(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static void	process_exit_with_arg(char **av, int argc)
{
	int		code;
	char	*stripped_arg;

	stripped_arg = strip_surrounding_quotes(av[1]);
	if (!stripped_arg)
		exit(1);
	if (!is_valid_number(stripped_arg))
	{
		handle_exit_error(av[1]);
		free(stripped_arg);
		exit(2);
	}
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		free(stripped_arg);
		return ;
	}
	code = ft_atoi(stripped_arg);
	free(stripped_arg);
	exit((unsigned char)code);
}

int	builtin_exit(t_minishell *sh, char **av)
{
	int	argc;

	if (sh->is_interactive)
		ft_putendl_fd("exit", 1);
	argc = count_exit_args(av);
	if (argc == 1)
		exit(sh->last_exit);
	process_exit_with_arg(av, argc);
	return (1);
}
