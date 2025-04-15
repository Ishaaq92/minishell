/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:19:35 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/15 17:32:02 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_commands
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_type
{
	LOGICAL_AND,
	LOGICAL_OR,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	PIPE,
	COMMAND,
	ARGS,
	PATH,
	ERROR,
};

// open_quote is used to mark the beginning of quoted text
typedef	struct s_token
{
	char			*literal;
	enum e_type		type;
	struct s_token	*next;
	struct s_token	*prev;
	int				open_quote;
}					t_token;

// abstract synatx tree nodes
typedef struct s_ast
{
	char				**literal;
	enum e_type			type;
	t_token				*token;
	struct s_ast		*left;
	struct s_ast		*right;
	struct s_ast		*parent;
}						t_ast;

// Handling Signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_z(int sig);
void	handle_signals(void);

// linked_list.c
void	print_tokens(t_token **head);
t_token	*ft_lstnew(char *str);
void	ft_lstadd_back(t_token **lst, t_token *new);

// tokens.c
int	create_tokens(char *str, t_token **head);

// utils.c
void    exit_cleanup(void);

// parser.c
void	parser(char *input, char *envp[]);

// ft_split2.c
char	**ft_split2(char *str, char *charset);

// ft_strndup.c
char	*ft_strndup(const char *s, int n);

// ast.c
t_ast	*parse_tokens(t_token *head);
void	print_ast(t_ast *ast, int i);
void	free_ast(t_ast *ast);

// ast_cmd.c
t_ast	*parse_cmd(t_token **node);
t_ast	*ast_new(t_token *token);

// ast_redir.c
t_ast	*parse_redir(t_token **token, t_token **stop);

#endif