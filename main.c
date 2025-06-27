/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 00:45:24 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minishell.h"

// void	print_ast(t_ast *n)
// {
// 	int	i;

// 	if (!n)
// 		return ;
// 	printf("CMD:");
// 	i = 0;
// 	while (n->cmd && n->cmd[i])
// 	{
// 		printf(" %s", n->cmd[i]);
// 		i++;
// 	}
// 	if (n->input)
// 		printf("  %s", n->input);            /* show input file   */
// 	if (n->output)
// 		printf(" %s %s",                    /* show output file  */
// 			n->append ? ">>" : "", n->output); /* distinguish >>    */
// 	printf("\n");
// 	print_ast(n->right);                        /* next pipeline cmd */
// }

// int main(void)
// {
// 	char	**w;
// 	t_ast	*ast;
// 	int		i;

// 	char *tests[] = {
// 		"ls -l",
// 	"echo > out.txt | ls -la | cat <<LIM | echo \"hello world $home\" >> out.txt",
// 		"grep foo < in.txt | wc -l >> log",
// 		NULL
// 	};
// 	i = 0;
// 	while (tests[i])
// 	{
// 		printf("Input: %s\n", tests[i]);
// 		w = ft_split_charset(tests[i], " \t");
// 		ast = parse_pipeline(w);
// 		print_ast(ast);
// 		free_ast(ast);
// 		ft_free_split(w);
// 		printf("\n");
// 		i++;
// 	}
// 	return (0);
// }
