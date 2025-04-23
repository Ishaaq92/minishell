
#include "../inc/minishell.h"

int		is_builtin(char *str);
int		execute_logical(t_ast *node, char **envp, t_envp *env_list);
int		execute_cmd(t_ast *node, char **envp, t_envp *env_list);
int		execute_redir(t_ast *node, char **envp, t_envp *env_list);

int	execute_node(t_ast *node, char **envp, t_envp *env_list)
{
	int	status;

	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		status = execute_logical(node, envp, env_list);
	else if (node->type == PIPE)
		status = execute_pipe(node, envp, env_list);
	else if (node->type > 1 && node->type < 6)
		status = execute_redir(node, envp, env_list);
	else if (node->type == COMMAND)
		status = execute_cmd(node, envp, env_list);
	return (status);
}

int	execute_logical(t_ast *node, char **envp, t_envp *env_list)
{
	int	status;

	status = execute_node(node->left, envp, env_list);
	if (node->type == LOGICAL_AND && status == 0)
		status = execute_node(node->right, envp, env_list);
	else if (node->type == LOGICAL_OR && status != 0)
		status = execute_node(node->right, envp, env_list);
	return (status);
}

int	execute_redir(t_ast *node, char **envp, t_envp *env_list)
{
	int		fd_newfile;
	int		fd_redir;

	if (ft_isdigit(node->token->literal[0]))
	{
		printf("isdigit");
	}
}

// TODO: change these numbers to macros
int	is_builtin(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
			return (2);
	else if (!ft_strcmp(str, "pwd"))
			return (3);
	else if (!ft_strcmp(str, "export"))
			return (4);
	else if (!ft_strcmp(str, "unset"))
			return (5);
	else if (!ft_strcmp(str, "env"))
			return (6);
	else if (!ft_strcmp(str, "exit"))
			return (7);
	else
		return (0);
}

int	execute_cmd(t_ast *node, char **envp, t_envp *env_list)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (is_builtin(node->literal[0]))
		;
		// return (); TODO
	set_cmd_path(node, env_list);
	if (pid == 0)
	{
		// child
		execve(node->literal[0], node->literal, envp);
	}
	else
	{
		// parent
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}


