/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/03 18:02:46 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_ast(t_ast *n)
{
	int	i;

	if (!n)
		return ;
	printf("CMD:");
	i = 0;
	while (n->cmd && n->cmd[i])
	{
		printf(" %s", n->cmd[i]);
		i++;
	}
	if (n->input)
		printf(" %s", n->input);
	if (n->output)
		printf(" %s %s", n->append ? ">>" : "", n->output);
	printf("\n");
	print_ast(n->right);
}

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

void init_minishell(t_minishell *sh, char **envp)
{
	size_t  n = 0;

	while (envp[n])
		++n;
	sh->env = malloc(sizeof(char *) * (n + 1));        /* plain malloc */
	if (!sh->env)
		exit(EXIT_FAILURE);
	for (size_t i = 0; i < n; ++i)
	{
		sh->env[i] = ft_strdup(envp[i]);               /* plain strdup */
		if (!sh->env[i])
			exit(EXIT_FAILURE);
	}
	sh->env[n] = NULL;
	sh->last_exit = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	t_ast		*ast;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&sh, envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// gc_init();
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (!quotes_balanced(line))
			ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		else if ((ast = parse_line(line, &sh)))
		{
			sh.last_exit = execute_ast(&sh, ast);
		}
		// gc_cleanup_all(); 
	}
	ft_putendl_fd("exit", 1);
	clear_history();
	return (sh.last_exit);
}
