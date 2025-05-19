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

#include "../../inc/minishell.h"

int		do_pipe_cmds(t_data *data, t_ast *node, int pipe_fd[2]);

int	execute_pipe(t_data *data, t_ast *node)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pid = fork();
	pipe(pipe_fd);
	if (pid == 0)
		do_pipe_cmds(data, node, pipe_fd);
	else
		waitpid(pid, &status, 0);
	close(pipe_fd[0]), close(pipe_fd[1]);
	return (WEXITSTATUS(status));
}

// do you need the entire data struct for this function?
int	do_pipe_cmds(t_data *data, t_ast *node, int pipe_fd[2])
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 failed"), 1);
		execute_node(data, node->left);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 failed"), 1);
		data->exit_status = execute_node(data, node->right);
		close(pipe_fd[0]);
	}
	del_lst(&data->env_llst);
	free_data(data);
	exit(data->exit_status);
}
