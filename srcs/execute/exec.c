
#include "../inc/minishell.h"

int		is_builtin(t_data *data, char *str);
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
int	is_builtin(t_data *data, char *str)
{
	if (!str)
		return (0);
	else if (!ft_strcmp(str, "echo"))
		return (0);
	else if (!ft_strcmp(str, "cd"))
		return (0);
	else if (!ft_strcmp(str, "pwd"))
		bi_pwd(data);
	else if (!ft_strcmp(str, "export"))
		return (0);
	else if (!ft_strcmp(str, "unset"))
		return (0);
	else if (!ft_strcmp(str, "env"))
		bi_env(data);
	else if (!ft_strcmp(str, "exit"))
		bi_exit(data);
	else
		return (0);
	return (1);
}

char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

// put me in coach
void	param_sub(t_data *data, char **str)
{
	int		i;
	char	*result;
	char	*sub_str;
	char	*temp;
	char	*temp2;
	char	*param;

	i = 0;
	result = NULL;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (result)
				free(result);
			result = ft_strndup((*str), i - 1);
			param = get_param_name((*str) + 1);
			temp = value_envp(&data->env_llst, param);
			temp2 = result;
			result = ft_strjoin(temp2, temp);
			free(temp2);
			// printf("s= %s\n", temp);
		}
		i++;
	}
	if (result)
	{
		free((*str));
		(*str) = result;
	}
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
			param_sub(data, &node->literal[i]);
			remove_quotes(node->literal[i]);
			i++;
		}
	}
}

int		execute_cmd(t_data *data, t_ast *node)
{
	pid_t	pid;

	if (is_builtin(data, node->literal[0]) != 0)
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
