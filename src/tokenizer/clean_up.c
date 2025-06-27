/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:57:57 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 00:45:35 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->text);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_ast(t_ast *node)
{
	t_ast	*next;
	int		i;

	while (node)
	{
		next = node->right;
		i = 0;
		if (node->cmd)
		{
			while (node->cmd[i])
			{
				free(node->cmd[i]);
				i++;
			}
			free(node->cmd);
		}
		free(node->input);
		free(node->output);
		free(node);
		node = next;
	}
}
