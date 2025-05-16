/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:21:33 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/16 12:05:40 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		do_pipe_cmds(t_data *data, t_ast *node);

int	execute_pipe(t_data *data, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		do_pipe_cmds(data, node);
	}
	else
	{
		waitpid(pid, &data->exit_status, 0);
	}
	return (WEXITSTATUS(data->exit_status));
}

// do you need the entire data struct for this function?
int	do_pipe_cmds(t_data *data, t_ast *node)
{
	int			fd[2];
	pid_t		pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 failed"), 1);
		execute_node(data, node->left);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 failed"), 1);
		data->exit_status = execute_node(data, node->right);
		close(fd[0]);
		// waitpid(pid, NULL, 0);
	}
	exit(data->exit_status);
}
