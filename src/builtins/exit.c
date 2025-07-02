/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:12 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 15:18:21 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_exit(t_minishell *sh, char **av)
{
	int	code;

	(void)sh;
	if (av[1])
		code = ft_atoi(av[1]);
	else
		code = 0;
	if (code < 0 || code > 255)
		code %= 256;
	printf("exit\n");
	exit(code);
}
