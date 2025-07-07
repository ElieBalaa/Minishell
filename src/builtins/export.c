/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:14 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/04 22:12:16 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	extend_env_array(t_minishell *sh, const char *str, int i)
{
	char	**new_env;

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

int	env_set(t_minishell *sh, const char *str)
{
	char	*equal;
	int		i;

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
			if (sh->env[i])
				return (0);
			else
				return (1);
		}
	}
	return (extend_env_array(sh, str, i));
}

static void	print_env_entry(const char *e)
{
	size_t	i;

	i = 0;
	while (e[i] && e[i] != '=')
		i++;
	write(1, "declare -x ", 11);
	write(1, e, i);
	if (e[i] == '=')
	{
		write(1, "=\"", 2);
		write(1, e + i + 1, strlen(e + i + 1));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

// int	builtin_export(t_minishell *sh, char **av)
// {
// 	int			i;
// 	int			err;
// 	size_t		j;
// 	char		*key;
// 	size_t		len;
// 	const char	*arg;

// 	i = 1;
// 	err = 0;
// 	if (!av[i])
// 	{
// 		i = 0;
// 		while (sh->env && sh->env[i])
// 		{
// 			print_env_entry(sh->env[i]);
// 			i++;
// 		}
// 		return (0);
// 	}
// 	while (av[i])
// 	{
// 		arg = av[i];
// 		len = 0;
// 		while (arg[len] && arg[len] != '=')
// 			len++;
// 		key = malloc(len + 1);
// 		if (!key)
// 			return (1);
// 		memcpy(key, arg, len);
// 		key[len] = '\0';
// 		if (!is_alpha_or_underscore(key[0]))
// 			err = 1;
// 		else
// 		{
// 			j = 1;
// 			while (key[j])
// 			{
// 				if (!is_alnum_or_underscore(key[j]))
// 				{
// 					err = 1;
// 					break ;
// 				}
// 				j++;
// 			}
// 		}
// 		if (err)
// 		{
// 			printf("minishell: export: `%s': not a valid identifier\n", key);
// 		}
// 		else if (arg[len] == '=')
// 		{
// 			if (env_set(sh, arg) != 0)
// 				err = 1;
// 		}
// 		free(key);
// 		i++;
// 	}
// 	return (err);
// }
static int	process_export_arg(t_minishell *sh, const char *arg)
{
	size_t	len;
	size_t	j;
	char	*key;
	int		err;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	key = malloc(len + 1);
	if (!key)
		return (1);
	ft_memcpy(key, arg, len);
	key[len] = '\0';
	err = !(ft_isalpha(key[0]) || key[0] == '_');
	j = 0;
	while (!err && key[++j])
		if (!(ft_isalnum(key[j]) || key[j] == '_'))
			err = 1;
	if (err)
		printf("minishell: export: `%s': not a valid identifier\n", key);
	else if (arg[len] == '=')
		if (env_set(sh, arg) != 0)
			err = 1;
	free(key);
	return (err);
}

int	builtin_export(t_minishell *sh, char **av)
{
	int	i;
	int	err;

	err = 0;
	if (!av[1])
	{
		i = 0;
		while (sh->env && sh->env[i])
			print_env_entry(sh->env[i++]);
		return (0);
	}
	i = 1;
	while (av[i])
	{
		err |= process_export_arg(sh, av[i]);
		++i;
	}
	return (err);
}
