/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 20:55:08 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

int	should_process_escape(char next_char, int in_single, int in_double)
{
	if (in_single)
		return (0);
	if (in_double)
		return (next_char == '"' || next_char == '\\' || next_char == '$');
	return (1);
}

static void	handle_character(const char *str, t_escape_ctx *ctx)
{
	int	should_escape;

	should_escape = should_process_escape(str[*(ctx->i) + 1],
			*(ctx->in_single), *(ctx->in_double));
	if (str[*(ctx->i)] == '\\' && str[*(ctx->i) + 1] && should_escape)
	{
		(*(ctx->i))++;
		ctx->result[(*(ctx->j))++] = str[*(ctx->i)];
	}
	else
	{
		if (str[*(ctx->i)] == '\'' && !*(ctx->in_double))
			*(ctx->in_single) = !*(ctx->in_single);
		else if (str[*(ctx->i)] == '"' && !*(ctx->in_single))
			*(ctx->in_double) = !*(ctx->in_double);
		ctx->result[(*(ctx->j))++] = str[*(ctx->i)];
	}
}

char	*process_token_escapes(t_minishell *sh, const char *str)
{
	int				i;
	int				j;
	int				in_single;
	int				in_double;
	char			*result;

	if (!str)
		return (NULL);
	result = gc_malloc(sh, ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		handle_character(str, &(t_escape_ctx){&i, &j, result,
			&in_single, &in_double});
		i++;
	}
	result[j] = '\0';
	return (result);
}
