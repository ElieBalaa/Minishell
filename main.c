/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:12:42 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/27 17:44:18 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	i = 0;
	printf("Tokens:\n");
	while (tokens[i])
	{
		printf("  Token %d: [%s]\n", i, tokens[i]->text);
		i++;
	}
}

// int	main(void)
// {
// 	char    *test_strings[] =
// 	{
// 		"ls -la",
// 		"echo hell	o	world",
// 		"  multiple   spaces  ",
// 		"",
// 		NULL
// 	};
// 	printf("Testing tokenizer:\n");
// 	printf("==================\n");
// 	for (int i = 0; test_strings[i]; i++)
// 	{
// 		printf("\nTest case %d: \"%s\"\n", i + 1, test_strings[i]);
// 		t_token **tokens = split_on_space(test_strings[i]);
// 		if (!tokens)
// 		{
// 			printf("Tokenizer returned NULL\n");
// 			continue ;
// 		}
// 		print_tokens(tokens);
// 		free_tokens(tokens);
// 	}
// 	printf("\nEdge case: NULL input\n");
// 	t_token **null_test = split_on_space(NULL);
// 	if (!null_test)
// 		printf("NULL input correctly handled\n");
// 	else
// 		printf("ERROR: NULL input not handled properly\n");
// 	return (0);
// }

int main(void)
{
    const char *tests[] = {
        "echo \"hello world\"",
        "echo 'foo bar'",
        "echo \"unclosed",
        "echo 'also unclosed",
        NULL
    };
    int j = 0;
    while (tests[j])
    {
        t_token **tokens;
        int       i;
        printf("Test %d: %s\n", j + 1, tests[j]);
        tokens = split_on_space((char *)tests[j]);
        if (!tokens)
        {
            fprintf(stderr, "tokenization failed\n");
            return (1);
        }
        if (check_if_quoted(tokens) < 0)
        {
            printf("=> Error: unclosed quote detected.\n\n");
        }
        else
        {
            i = 0;
            while (tokens[i])
            {
                printf("token[%d] = '%s'\n", i, tokens[i]->text);
                i++;
            }
            printf("\n");
        }
        free_tokens(tokens);
        j++;
    }
    return (0);
}
