
#include "../inc/minishell.h"

void	execute_logical(t_ast *node, char **envp, t_envp *env_list);
int		execute_cmd(t_ast *node, char **envp, t_envp *env_list);

void	execute_ast(t_ast *node, char **envp, t_envp *env_list)
{
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		execute_logical(node, envp, env_list);
	if (node->type == COMMAND)
		execute_cmd(node, envp, env_list);
}

void	execute_logical(t_ast *node, char **envp, t_envp *env_list)
{
	int	status;

	status = execute_cmd(node->left, envp, env_list);
	if (node->type == LOGICAL_AND && status == 0)
		execute_cmd(node->right, envp, env_list);
	else if (node->type == LOGICAL_OR && status != 0)
		execute_cmd(node->right, envp, env_list);
}

int	execute_cmd(t_ast *node, char **envp, t_envp *env_list)
{
	int	pid;
	int	status;

	pid = fork();
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


