/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/08 21:11:21 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	process_line(t_minishell *sh, char *line)
{
	t_ast	*ast;

	if (!quotes_balanced(line))
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
	else
	{
		ast = parse_line(line, sh);
		if (ast)
		{
			sh->last_exit = execute_ast(sh, ast);
			gc_cleanup_all(sh);
		}
	}
}

static void	setup_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&sh, envp);
	setup_signals();
	line = readline("minishell> ");
	while (line)
	{
		if (*line)
			add_history(line);
		process_line(&sh, line);
		free(line);
		line = readline("minishell> ");
	}
	cleanup_shell(&sh);
	return (sh.last_exit);
}
