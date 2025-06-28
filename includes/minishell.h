/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:13:22 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/28 15:07:59 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_simple_gc
{
	t_gc_node	*head;
	int			count;
}	t_simple_gc;

typedef struct s_token
{
	char				*text;
	struct s_token		*next;
}	t_token;

typedef struct s_ast
{
	char			**cmd;
	char			*input;
	char			*output;
	int				append;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

extern t_simple_gc	g_gc;

			/*cleen up.c*/
void	ft_free_split(char **str);
void	free_tokens(t_token **tokens);
void	free_ast(t_ast *node);
void	free_toklist(t_token *lst);

			/*tokenization.c*/
t_token	**split_on_space(char *str);
t_ast	*parse_pipeline(char **words);
t_ast	*parse_segment(char **tokens, int n);
t_token	*tok_last(t_token *lst);
t_token	*tokenize(const char *line);
t_ast	*parse_line(const char *line);
char	**tok_to_array(t_token *lst);

			/*utils.c*/
int		is_quoted(char *str);
int		is_operator(char c);
int		is_space(char c);
int		is_redir(char *s);
int		count_args(char **tok, int n);
int		op_len(const char *s);
			/*garbage collecter*/
int		gc_init(void);
void	gc_cleanup_all(void);
void	gc_emergency_cleanup(int sig);
void	*gc_malloc(size_t size);
char	*gc_strdup(const char *s);
int		gc_add(void *ptr);
t_token	**gc_split_on_space(char *str);
int		is_whitespace(char c);
int		count_words(char *str);
char	*extract_word(char *str, int *start);
char	**split_whitespace(char *str);

#endif