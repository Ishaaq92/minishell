/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:07:45 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/15 18:08:54 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exec_child(char **cmd, t_envp *env_list);

// TODO: change these numbers to macros
int	is_builtin(t_data *data, t_ast *node)
{
	if (!node)
		return (0);
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
	else
		return (0);
	return (1);
}

void	clean_args(t_data *data)
{
	t_token	*temp;
	t_token	*list;

	temp = data->token_list;
	list = NULL;
	while (temp)
	{
		if (temp->type == WORD)
			if (temp->literal)
			{
				if (ft_strchr(temp->literal, '$'))
				{
					param_sub(data, &temp->literal);
					create_tokens(temp->literal, &list);
					t_token		*temp3;

					temp3 = list;
					while (temp3)
					{
						temp3->type = WORD;
						temp3 = temp3->next;
					}
					if (list->next)
					{
						t_token	*temp2;
						t_token	*list_last;

						temp2 = temp->prev;
						if (temp2)
							temp2->next = list;
						else
							data->token_list = list;
						list->prev = temp2;
						list_last = ft_lstlast(list);
						list_last->next = temp->next;
						temp2 = temp->next;
						if (temp2)
							temp2->prev = list_last;
						ft_lstdelone(temp);
						temp = list;
					}
				}
				remove_quotes(temp->literal);
			}
		temp = temp->next;
		list = NULL;
	}
}

int	execute_cmd(t_data *data, t_ast *node)
{
	pid_t	pid;

	clean_args(data);
	if (is_builtin(data, node))
		return (data->exit_status);
	if (!ft_strcmp(node->literal[0], ".."))
		return (custom_error(node->literal[0], "command not found"), 127);
	else if (!ft_strncmp(node->literal[0], "./", 2) || node->literal[0][0] == '/')
	{
		if (access(node->literal[0], F_OK))
			return (custom_error(node->literal[0], "No such file or directory"), 127);
		if (access(node->literal[0], X_OK))
			return (custom_error(node->literal[0], "Permission denied"), 126);
	}
	else if (find_cmd_path(node, data->env_llst))
	{
		// if (!access(node->literal[0], F_OK) && access(node->literal[0], X_OK))
		// 	return (custom_error(node->literal[0], "Permission denied"), 126);
		if (ft_strchr(node->literal[0], '/'))
			custom_error(node->literal[0], "No such file or directory");
		else
			custom_error(node->literal[0], "command not found");
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
		(custom_error("malloc", "memory allocation failed"), exit(EXIT_FAILURE));
	if (dir)
		(custom_error(cmd[0], "Is a directory"), closedir(dir), exit(126));
	execve(cmd[0], cmd, envp);
	exit(EXIT_FAILURE);
}
