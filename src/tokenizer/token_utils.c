/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:11:09 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 14:36:37 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	op_len(const char *s)
{
	if ((s[0] == '<' || s[0] == '>') && s[1] == s[0])
		return (2);
	return (1);
}

t_token	*tok_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
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
