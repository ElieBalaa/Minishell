/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:13:22 by oiskanda          #+#    #+#             */
/*   Updated: 2025/07/02 20:04:41 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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

typedef struct s_minishell
{
	char	**env;
	int		last_exit;
}	t_minishell;

extern t_simple_gc	g_gc;

			/*clean up.c*/
void				ft_free_split(char **str);
void				free_tokens(t_token **tokens);
void				free_ast(t_ast *node);
void				free_toklist(t_token *lst);
char				*ft_strndup(const char *s, int n);

				/*tokenization.c*/
t_token				**split_on_space(char *str);
t_token				*tok_last(t_token *lst);
t_token				*tokenize(const char *line, int last_exit);
t_ast				*parse_pipeline(char **words);
t_ast				*parse_segment(char **tokens, int n);
t_ast				*parse_line(const char *line, int last_exit);
t_ast				*init_ast_node(void);
int					is_pipeline_end(char **w, int i);
char				**tok_to_array(t_token *lst);
const char			*skip_quotes(const char *p);
char				*expand_vars(const char *s, int last_exit);

				/*escape_utils.c*/
int					should_process_escape(char next_char,
						int in_single, int in_double);
char				*process_token_escapes(const char *str);

				/*execution.c*/
int					execute_ast(t_minishell *sh, t_ast *ast);
char				*resolve_command_path(const char *cmd);
int					fork_and_execute(t_minishell *sh,
						const char *path, char **argv);

				/*builtins.c*/
int					builtin_exit(t_minishell *sh, char **args);
int					builtin_echo(t_minishell *sh, char **args);
int					builtin_cd(t_minishell *sh, char **args);
int					builtin_pwd(t_minishell *sh, char **args);
int					builtin_env(t_minishell *sh, char **argv);
int					builtin_export(t_minishell *sh, char **args);
int					builtin_unset(t_minishell *sh, char **args);
int					execute_builtin(t_minishell *sh, char **args);
int					is_valid_key(const char *s);
int					env_count(char **e);
char				**env_copy(char **env);
void				sort_strings(char **arr);
int					handle_export_arg(t_minishell *sh, char *arg);
int					env_set(t_minishell *sh, const char *str);
void				env_unset(t_minishell *sh, const char *key);

				/*utils.c*/
int					is_quoted(char *str);
int					is_operator(char c);
int					is_space(char c);
int					is_redir(char *s);
int					count_args(char **tok, int n);
int					op_len(const char *s);
int					quotes_balanced(const char *s);
char				*strip_surrounding_quotes(const char *str);
void				process_redir(char **tok, int *i, t_ast *node);
int					ft_tokensize(t_token *lst);

				/*garbage collector*/
int					gc_init(void);
void				gc_cleanup_all(void);
void				*gc_malloc(size_t size);
char				*gc_strdup(const char *s);
char				*gc_strndup(const char *s, int n);
int					gc_add(void *ptr);
t_token				**gc_split_on_space(char *str);
int					is_whitespace(char c);
int					count_words(char *str);
char				*extract_word(char *str, int *start);
char				**split_whitespace(char *str);
char				*gc_strjoin(const char *s1, const char *s2);
char				*gc_itoa(int n);
char				*qc_remove_quotes(const char *s);


#endif