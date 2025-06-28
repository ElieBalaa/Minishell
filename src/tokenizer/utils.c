/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:33:19 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 14:33:40 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, ">>") == 0);
}

int	count_args(char **tok, int n)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (++i < n)
	{
		if (is_redir(tok[i]))
			i++;
		else
			cnt++;
	}
	return (cnt);
}