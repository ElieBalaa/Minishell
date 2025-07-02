/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:33:19 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/30 16:57:01 by oiskanda         ###   ########.fr       */
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

	if (!tok || n <= 0)
		return (0);
	i = 0;
	cnt = 0;
	while (i < n && tok[i])
	{
		if (is_redir(tok[i]))
		{
			i += 2;
			if (i >= n)
				break ;
		}
		else
		{
			cnt++;
			i++;
		}
	}
	return (cnt);
}

int	quotes_balanced(const char *s)
{
	int	i;
	int	singles;
	int	doubles;

	singles = 0;
	doubles = 0;
	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			singles++;
		else if (s[i] == '"')
			doubles++;
		i++;
	}
	return (singles % 2 == 0 && doubles % 2 == 0);
}

char	*strip_surrounding_quotes(const char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		return (ft_strndup(str + 1, len - 2));
	}
	return (ft_strdup(str));
}

t_token	**split_on_space(char *str)
{
	int		i;
	t_token	*tok;
	char	**words;
	t_token	**tokens;

	if (!str)
		return (NULL);
	words = split_whitespace(str);
	if (!words)
		return (NULL);
	tokens = malloc(sizeof(t_token *)
			* (count_double_array(words) + 1));
	i = -1;
	while (++i < count_double_array(words))
	{
		tok = malloc(sizeof(t_token));
		if (!tok)
			ft_putstr_fd("malloc failed", 2);
		tok->text = ft_strdup(words[i]);
		tok->next = NULL;
		tokens[i] = tok;
	}
	tokens[count_double_array(words)] = NULL;
	return (tokens);
}
