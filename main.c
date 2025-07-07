/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/04 19:56:08 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	status_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (wstatus);
}

void	init_minishell(t_minishell *sh, char **envp)
{
	size_t	n;
	size_t	i;

	n = 0;
	while (envp[n])
		n++;
	sh->env = malloc(sizeof(char *) * (n + 1));
	if (!sh->env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		sh->env[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->env[n] = NULL;
	sh->last_exit = 0;
	gc_init(sh);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&sh, envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell> ");
	while (line)
	{
		if (*line)
			add_history(line);
		process_line(&sh, line);
		free(line);
		line = readline("minishell> ");
	}
	ft_putendl_fd("exit", 1);
	clear_history();
	gc_cleanup_all(&sh);
	return (sh.last_exit);
}
