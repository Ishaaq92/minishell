
#include "../inc/minishell.h"

int		is_builtin(t_data *data, t_ast *node);
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
int	is_builtin(t_data *data, t_ast *node)
{
	if (!node)
		return (0);
	else if (!ft_strcmp(node->literal[0], "echo"))
		bi_echo(data, node);
	else if (!ft_strcmp(node->literal[0], "cd"))
		bi_cd(data, node);
	else if (!ft_strcmp(node->literal[0], "pwd"))
		bi_pwd(data);
	else if (!ft_strcmp(node->literal[0], "export"))
		bi_export(data, node->literal[0]);
	else if (!ft_strcmp(node->literal[0], "unset"))
		bi_unset(data, node->literal[0]);
	else if (!ft_strcmp(node->literal[0], "env"))
		bi_env(data);
	else if (!ft_strcmp(node->literal[0], "exit"))
		bi_exit(data);
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
	if (is_builtin(data, node) != 0)
		return (0);
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
