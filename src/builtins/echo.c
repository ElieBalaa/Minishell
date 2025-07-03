/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:16:07 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/03 18:01:49 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_minishell *sh, char **av)
{
	int	i;
	int	nl;

	(void)sh;
	nl = 1;
	i = 1;
	if (av[1] && !ft_strcmp(av[1], "-n"))
		(nl = 0, i = 2);
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		++i;
	}
	if (nl)
		printf("\n");
	return (0);
}


// int  builtin_echo(t_minishell *sh, char **av)
// {
// 	int   i = 1, nl = 1;
// 	char  *expanded;

// 	(void)sh;
// 	if (av[1] && !ft_strcmp(av[1], "-n"))
// 		nl = 0, i = 2;
// 	while (av[i])
// 	{
// 		expanded = expand_vars(av[i], sh->last_exit);
// 		printf("%s", expanded);
// 		if (av[i + 1])
// 			putchar(' ');
// 		++i;
// 	}
// 	if (nl)
// 		putchar('\n');
// 	return (0);
// }