/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/02 14:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static char	*check_direct_path(const char *cmd)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (gc_strdup(cmd));
		}
	}
	return (NULL);
}

static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*path;
	char	*temp;

	temp = gc_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = gc_strjoin(temp, cmd);
	return (path);
}

static char	*search_in_path_dirs(const char *cmd, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = build_full_path(path_dirs[i], cmd);
		if (full_path && access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
		}
		i++;
	}
	return (NULL);
}

char	*resolve_command_path(const char *cmd)
{
	char	*path_env;
	char	**path_dirs;
	char	*result;

	result = check_direct_path(cmd);
	if (result)
		return (result);
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	result = search_in_path_dirs(cmd, path_dirs);
	ft_free_split(path_dirs);
	return (result);
}
