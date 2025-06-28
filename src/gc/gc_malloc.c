/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 22:54:56 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add(ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

char	*gc_strdup(const char *s)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	if (!gc_add(dup))
	{
		free(dup);
		return (NULL);
	}
	return (dup);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	int		len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gc_strndup(const char *s, int n)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = ft_strndup(s, n);
	if (!dup)
		return (NULL);
	if (!gc_add(dup))
	{
		free(dup);
		return (NULL);
	}
	return (dup);
}
