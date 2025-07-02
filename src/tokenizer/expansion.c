/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:54 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 17:57:37 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_length(const char *str)
{
	int	length;

	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	length = 1;
	while (str[length] && (ft_isalnum(str[length]) || str[length] == '_'))
		length++;
	return (length);
}

static char	*expand_special_var(int *adv, int last_exit)
{
	*adv = 1;
	return (gc_itoa(last_exit));
}

static char	*expand_normal_var(const char *str, int *adv)
{
	char	*var_name;
	char	*var_value;

	*adv = get_var_length(str);
	if (*adv == 0)
		return (gc_strdup("$"));
	var_name = gc_strndup(str, *adv);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	return (gc_strdup(var_value));
}

static void	handle_quotes(char *str, size_t *i, int *in_quotes, char **result)
{
	char	quote;

	quote = str[*i];
	in_quotes[quote == '\''] ^= 1;
	*result = gc_strjoin(*result, gc_strndup(&quote, 1));
	(*i)++;
}

char	*expand_vars(const char *str, int last_exit)
{
	size_t	i;
	int		in_quotes[2];
	int		adv;
	char	*tmp;
	char	*result;

	if (!str)
		return (NULL);
	result = gc_strdup("");
	in_quotes[0] = 0;
	in_quotes[1] = 0;
	i = 0;
	while (str[i])
	{
		if (((str[i] == '"') && !in_quotes[0])
			|| (str[i] == '\'' && !in_quotes[1]))
			handle_quotes((char *)str, &i, in_quotes, &result);
		else if (str[i] == '$' && !in_quotes[0])
		{
			tmp = (str[i + 1] == '?') ? expand_special_var(&adv, last_exit) \
				: expand_normal_var(str + i + 1, &adv);
			result = gc_strjoin(result, tmp);
			i += adv + 1;
		}
		else
			result = gc_strjoin(result, gc_strndup(str + i++, 1));
	}
	return (result);
}

