/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:19:35 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/21 19:40:01 by isahmed          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h> // for wait functions
# include <sys/types.h>
# include <dirent.h> // for opendir
# include <stdarg.h>
# include <limits.h>
# include <sys/ioctl.h>

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

typedef enum e_type
{
	LOGICAL_AND,
	LOGICAL_OR,
	REDIR_IN,
	REDIR_OUT,
	OUT_APPEND,
	IN_HEREDOC,
	PIPE,
	WORD,
	ARGS,
	PATH,
	LBRACE,
	RBRACE,
	ERROR,
}		t_type;

// open_quote is used to mark the beginning of quoted text
typedef struct s_token
{
	char				*literal;
	enum e_type			type;
	struct s_token		*next;
	struct s_token		*prev;
	int					open_quote;
	int					fd;
}						t_token;

// abstract synatx tree nodes
typedef struct s_ast
{
	char				**literal;
	enum e_type			type;
	t_token				*token;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

// linked list to hold the environment variables unique to our shell
typedef struct s_envp
{
	char				*literal;
	struct s_envp		*next;
}						t_envp;

typedef struct s_data
{
	t_envp				*env_llst;
	t_token				*token_list;
	t_ast				*head;
	int					exit_status;
	int					std_fd[3];
}						t_data;

// "main" minishell.c
void	free_data(t_data *data);

// Handling Signals
void	handle_ctrl_c(int sig);
void	handle_signals(void);
void	handle_signals(void);
void	set_signal(int sig);
int		get_signal(void);

// linked_list.c
t_token	*ft_lstnew(char *str);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
t_token	*ft_lstlast(t_token *lst);

// tokens.c
int		create_tokens(char *str, t_token **head);

// tokens_utils.c
int		is_op(char c);
int		is_blank(char c);
t_type	set_op_type(char *str);
int		check_valid_order(t_token **head);

// utils.c
void	exit_cleanup(t_data *data);
int		ft_strcmp(char *s1, char *s2);
int		custom_error(char *str, char *msg);
int		bi_custom_error(char *func, char *str, char *msg);
void	reset_redir(t_data *data);

// prompt.c
char	*get_prompt(int exit_status);

// ft_strndup.c
char	*ft_strndup(const char *s, int n);

// ast.c
t_ast	*parse_tokens(t_token *head);

// ast_utils.c
t_ast	*ast_new(t_token *token);
void	print_ast(t_ast *ast, int i);
void	free_ast(t_ast *ast);
t_token	*get_rbrace(t_token *lbrace);
void	skip_braces(t_token **temp);

// ast_cmd.c
t_ast	*parse_cmd(t_token **token);
char	**parse_cmd_args(t_token *token, int argc);
int		count_argc(t_token *token);

// ast_redir.c
t_ast	*parse_redir(t_token **token, t_token **stop);

// clean_args.c
void	clean_args(t_data *data, t_ast *node);
void	reset_node_literal(t_ast *node);

// heredoc.c
int		parse_heredoc(t_data *data, t_token *token);

// Execution

// env_delete.c
void	remove_node(t_data *data, char *var);
void	del_array(char **envp);
void	del_lst(t_envp **lst);

// env_create.c
int		add_node(t_data *data, char *string);
char	**stitch_env(t_envp *head);
t_envp	*set_envp(char **envp);
void	env_alter(t_data *data, char *key, char *value);

// env_utils.c
t_envp	*check_envp(t_data *data, char *key);
void	print_envp(t_envp **lst);
void	env_lstadd_back(t_envp **lst, t_envp *new);
char	*value_envp(t_envp **lst, char *str);

// cmd_path.c
int		find_cmd_path(t_ast *node, t_envp *env_list);

// exec.c
int		execute_node(t_data *data, t_ast *node);

// exec_pipe.c
int		execute_pipe(t_data *data, t_ast *node);

// exec_redir.c
int		execute_redir(t_data *data, t_ast *node);

// exec_cmd.c
int		execute_cmd(t_data *data, t_ast *node);

// wildcards.c
void	wildcards(t_data *data);
void	ft_lstdelone(t_token *args);

// wildcard_helper.c
int		get_wildcard_args(t_token *args, t_token **wild_args);

// quote_removal.c
void	remove_quotes(char *str);

// param_sub.c
void	param_sub(t_data *data, char **str, int heredoc);
char	*get_param_name(char *str);

// bi_cd.c
int		bi_cd(t_data *data, t_ast *node);

// bi_echo.c
int		bi_echo(t_data *data, t_ast *node);

// bi_export.c
int		bi_export(t_data *data, t_ast *node);

// bi_the_rest.c
int		bi_pwd(t_data *data);
int		bi_env(t_data *data);
int		bi_exit(t_data *data, t_ast *node);
int		bi_unset(t_data *data, t_ast *node);

// debug.c
void	print_tokens(t_token **head);

#endif
