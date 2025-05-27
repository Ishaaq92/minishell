/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/27 14:56:00 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exec_child(t_data *data, char **cmd);
static int	is_builtin(t_data *data, t_ast *node);
static int	check_cmd(t_data *data, t_ast *node, char *cmd);
int			child_exit_status(int status);

int	execute_cmd(t_data *data, t_ast *node)
{
	pid_t	pid;
	int		error;

	clean_args(data, node);
	if (is_builtin(data, node))
		return (data->exit_status);
	error = check_cmd(data, node, node->literal[0]);
	if (error)
		return (error);
	reset_node_literal(node);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_child(data, node->literal);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &data->exit_status, 0);
		handle_signals();
	}
	return (child_exit_status(data->exit_status));
}

int	child_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static void	exec_child(t_data *data, char **cmd)
{
	DIR		*dir;
	char	**envp;
	int		i;

	dir = opendir(cmd[0]);
	envp = stitch_env(data->env_llst);
	if (!envp)
		(custom_error("env list", "malloc failed"), exit(EXIT_FAILURE));
	if (dir)
		(custom_error(cmd[0], "Is a directory"), closedir(dir), exit(126));
	execve(cmd[0], cmd, envp);
	custom_error("uh oh", "execve failed\n");
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	(del_lst(&data->env_llst), free_data(data));
	exit(EXIT_FAILURE);
}

static int	is_builtin(t_data *data, t_ast *node)
{
	signal(SIGPIPE, SIG_IGN);
	if (!node || !node->literal[0])
	{
		custom_error("", "command not found");
		data->exit_status = 127;
	}
	else if (!ft_strcmp(node->literal[0], "echo"))
		data->exit_status = bi_echo(data, node);
	else if (!ft_strcmp(node->literal[0], "cd"))
		data->exit_status = bi_cd(data, node);
	else if (!ft_strcmp(node->literal[0], "pwd"))
		data->exit_status = bi_pwd(data);
	else if (!ft_strcmp(node->literal[0], "export"))
		data->exit_status = bi_export(data, node);
	else if (!ft_strcmp(node->literal[0], "unset"))
		data->exit_status = bi_unset(data, node);
	else if (!ft_strcmp(node->literal[0], "env"))
		data->exit_status = bi_env(data);
	else if (!ft_strcmp(node->literal[0], "exit"))
		data->exit_status = bi_exit(data, node);
	else if (!ft_strcmp(node->literal[0], ":"))
		data->exit_status = 0;
	else
		return (signal(SIGPIPE, SIG_DFL), 0);
	return (signal(SIGPIPE, SIG_DFL), 1);
}

static int	check_cmd(t_data *data, t_ast *node, char *cmd)
{
	if (!ft_strcmp(cmd, "..") || !ft_strcmp(cmd, "."))
		return (custom_error(cmd, "command not found"), 127);
	else if (!ft_strncmp(cmd, "./", 2) || cmd[0] == '/')
	{
		if (access(cmd, F_OK))
			return (custom_error(cmd, "No such file or directory"), 127);
		if (access(cmd, X_OK))
			return (custom_error(cmd, "Permission denied"), 126);
	}
	else if (find_cmd_path(node, data->env_llst))
	{
		if (ft_strchr(cmd, '/'))
			custom_error(cmd, "No such file or directory");
		else
			custom_error(cmd, "command not found");
		return (127);
	}
	return (0);
}
