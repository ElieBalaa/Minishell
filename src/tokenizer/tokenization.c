/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:29 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/27 13:18:17 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	**split_on_space(char *str)
{
	int		i;
	t_token	*tok;
	char	**words;
	t_token	**tokens;

	if (!str)
		return (NULL);
	words = ft_split(str, ' ');
	tokens = (t_token **)malloc(sizeof(t_token *)
			* (count_double_array(words) + 1));
	if (!words || !tokens)
		return (NULL);
	i = -1;
	while (++i < count_double_array(words))
	{
		tok = (t_token *)malloc(sizeof(t_token));
		if (!tok)
			ft_putstr_fd("malloc failed", 2);
		tok->text = ft_strdup(words[i]);
		tok->next = NULL;
		tokens[i] = tok;
	}
	tokens[count_double_array(words)] = NULL;
	ft_free_split(words);
	return (tokens);
}

void	classify_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i]->text, "|") == 0)
			tokens[i]->type = T_PIPE;
		else if (ft_strcmp(tokens[i]->text, "<") == 0)
			tokens[i]->type = T_REDIR_IN;
		else if (ft_strcmp(tokens[i]->text, ">") == 0)
			tokens[i]->type = T_REDIR_OUT;
		else if (ft_strcmp(tokens[i]->text, ">>") == 0)
			tokens[i]->type = T_APPEND;
		else if (ft_strcmp(tokens[i]->text, "<<") == 0)
			tokens[i]->type = T_HEREDOC;
		else
			tokens[i]->type = T_WORD;
		i++;
	}
}

