/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:13:22 by oiskanda          #+#    #+#             */
/*   Updated: 2025/06/27 17:36:43 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

typedef enum e_token_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_WORD
}	t_type;

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

typedef struct s_ast
{
	char			**cmd;
	char			*input;
	char			*output;
	struct s_ast	*right;
}	t_ast;

typedef struct s_token
{
	t_type				type;
	char				*text;
	struct s_token		*next;
}	t_token;

extern t_simple_gc	g_gc;

void	ft_free_split(char **str);
void	free_tokens(t_token **tokens);
int		count_double_array(char **str);

t_token	**split_on_space(char *str);
int		check_if_quoted(t_token **tokens);
int 	is_quoted(char *str);

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