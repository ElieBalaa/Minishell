/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:11:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 00:11:03 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_quoted(char *str)
{
	int	j;
	int	count_double;
	int	count_single;

	j = 0;
	count_double = 0;
	count_single = 0;
	while (str[j])
	{
		if (str[j] == '"')
			count_double++;
		if (str[j] == '\'')
			count_single++;
		j++;
	}
	if ((count_double && (count_double % 2 == 0))
		|| (count_single && (count_single % 2 == 0)))
		return (1);
	return (0);
}

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
