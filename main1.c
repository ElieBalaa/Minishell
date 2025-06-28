/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 23:10:59 by oiskanda         ###   ########.fr       */
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

int main(void)
{
    while (1)
    {
        gc_init();
        char *line = readline("minishell> ");
        printf("Input: %s\n", line);
        if (!quotes_balanced(line))
        {
            fprintf(stderr, "minishell: syntax error: unclosed quote\n\n");
            continue;
        }
        char **words = ft_split_charset(line, " \t");
        if (!words)
        {
            fprintf(stderr, "Error: failed to split line\n\n");
            continue;
        }
        t_ast *ast = parse_pipeline(words);
        if (!ast)
        {
            fprintf(stderr, "Error: failed to parse AST\n\n");
            ft_free_split(words);
            continue;
        }
        print_ast(ast);
        gc_cleanup_all();
        printf("\n");
    }
    return 0;
}
