
#include "../inc/minishell.h"

static void	exec_child(char **cmd, t_envp *env_list);

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
	if (node->type == WORD)
	{
		while (node->literal[i])
		{
			param_sub(data, &node->literal[i]);
			remove_quotes(node->literal[i]);
			i++;
		}
	}
}

int	execute_cmd(t_data *data, t_ast *node)
{
	pid_t	pid;

	clean_args(data, node);
	if (is_builtin(data, node))
		return (data->exit_status);
	if (find_cmd_path(node, data->env_llst))
	{
		if (ft_strchr(node->literal[0], '/'))
			custom_error(node->literal[0], "No such file or directory\n");
		else
			custom_error(node->literal[0], "command not found\n");
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		exec_child(node->literal, data->env_llst);
	}
	else
	{
		waitpid(pid, &data->exit_status, 0);
	}
	return (WEXITSTATUS(data->exit_status));
}

static void	exec_child(char **cmd, t_envp *env_list)
{
	DIR		*dir;
	char	**envp;

	dir = opendir(cmd[0]);
	envp = stitch_env(env_list);
	if (!envp)
		(custom_error("malloc: ", "memory allocation failed\n"), exit(EXIT_FAILURE));
	if (dir)
		(custom_error(cmd[0], "Is a directory\n"), closedir(dir), exit(126));
	execve(cmd[0], cmd, envp);
	exit(EXIT_FAILURE);
}
