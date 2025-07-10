/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:00 by oiskanda          #+#    #+#             */
/*   Updated: 2025/01/14 15:00:00 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_prompt(void)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
}

int	find_last_delimiter_index(char **delimiters)
{
	int	i;

	if (!delimiters)
		return (-1);
	i = 0;
	while (delimiters[i])
		i++;
	return (i - 1);
}
