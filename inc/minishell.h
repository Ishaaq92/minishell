/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:19:35 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/28 14:28:40 by ishaaq           ###   ########.fr       */
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
	BRACKET_START,
	BRACKET_END,
	ERROR,
};

// open_quote is used to mark the beginning of quoted text
typedef	struct s_token
{
	char				*literal;
	enum e_type			type;
	struct s_token		*next;
	struct s_token		*prev;
	int					open_quote;
}						t_token;

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
	char				**envp;
	t_ast				*head;
	int					exit_status;
	int					std_fd[3];
}						t_data;

// "main" minishell.c
t_data	*init_exec_data(char *line, char **envp);

// Handling Signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_z(int sig);
void	handle_signals(void);

// linked_list.c
void	print_tokens(t_token **head);
t_token	*ft_lstnew(char *str);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);

// tokens.c
int	create_tokens(char *str, t_token **head);

// utils.c
void    exit_cleanup(t_data *data);
int		ft_strcmp(char *s1, char *s2);

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

// Execution

// env_delete.c
void	remove_node(t_envp **lst, char ***envp, char *var);
void	del_array(char **envp);
void	del_lst(t_envp **lst);

// env_create.c
char	**stitch_env(t_envp *head);
t_envp	*set_envp(char **envp);
void	append_node(t_envp **lst, char **array, char *string);
void	env_alter(t_data *data, char *key, char *value);

// env_utils.c
void	print_envp(t_envp **lst);
void	env_lstadd_back(t_envp **lst, t_envp *new);
char	*value_envp(t_envp **lst, char *str);

// cmd_path.c
int		set_cmd_path(t_ast *node, t_envp *env_list);

// exec.c
int		execute_node(t_data *data, t_ast *node);

// exec_pipe.c
int		execute_pipe(t_data *data, t_ast *node);

// exec_redir.c
int		execute_redir(t_data *data, t_ast *node);

// quote_removal.c
void		remove_quotes(char *str);

// param_sub.c
void	param_sub(t_data *data, char **str);


// bi_func.c
void	bi_pwd(t_data *data);
int		bi_cd(t_data *data, t_ast *node);
void	bi_env(t_data *data);
void	bi_export(t_data *data, char *str);
void	bi_exit(t_data *data);
void	bi_unset(t_data *data, char *str);
void	bi_echo(t_data *data, t_ast *node);


#endif