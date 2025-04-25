
#include "../inc/minishell.h"

int		is_builtin(char *str, t_ast *node);
int		execute_logical(t_data *data, t_ast *node);
int		execute_cmd(t_data *data, t_ast *node);

int		execute_node(t_data *data, t_ast *node)
{
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		data->exit_status = execute_logical(data, node);
	else if (node->type == PIPE)
		data->exit_status = execute_pipe(data, node);
	else if (node->type > 1 && node->type < 6)
		data->exit_status = execute_redir(data, node);
	else if (node->type == COMMAND)
		data->exit_status = execute_cmd(data, node);
	return (data->exit_status);
}

int		execute_logical(t_data *data, t_ast *node)
{
	data->exit_status = execute_node(data, node->left);
	if (node->type == LOGICAL_AND && data->exit_status == 0)
		data->exit_status = execute_node(data, node->right);
	else if (node->type == LOGICAL_OR && data->exit_status != 0)
		data->exit_status = execute_node(data, node->right);
	return (data->exit_status);
}

// TODO: change these numbers to macros
int	is_builtin(char *str, t_ast *node)
{
	if (!str)
		return (0);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (2);
		// bi_cd(node);
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
	return (1);
}

void	clean_args(t_data *data, t_ast *node)
{
	int		i;

	i = 0;
	if (node->type == COMMAND)
	{
		while (node->literal[i])
		{
			// parameter expansion at this step
			remove_quotes(node->literal[i]);
			i++;
		}
	}
}

int		execute_cmd(t_data *data, t_ast *node)
{
	pid_t	pid;

	// if (is_builtin(node->literal[0], node) != 0)
		// return (); TODO
	
	set_cmd_path(node, data->env_llst);
	clean_args(data, node);
	pid = fork();
	if (pid == 0)
	{
		// child
		execve(node->literal[0], node->literal, data->envp);
	}
	else
	{
		// parent
		waitpid(pid, &data->exit_status, 0);
	}
	return (WEXITSTATUS(data->exit_status));
}
