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

// int		do_pipe_cmds(t_data *data, t_ast *node, int pipe_fd[2]);
// int	pipe_cmd1(t_data *data, t_ast *node, int pipe_fd[2]);
// int	pipe_cmd2(t_data *data, t_ast *node, int pipe_fd[2]);
static pid_t	pipe_cmd(t_data *data, t_ast *node, int fd, int pipe_fd[2]);

int	execute_pipe(t_data *data, t_ast *node)
{
	pid_t	pid[2];
	int		pipe_fd[2];
	int		status[2];

	if (pipe(pipe_fd) < 0)
		return (perror("pipe failed"), 1);
	pid[0] = pipe_cmd(data, node->left, 0, pipe_fd);
	if (pid[0] < 0)
		return (1);
	pid[1] = pipe_cmd(data, node->right, 1, pipe_fd);
	if (pid[1] < 0)
		return (1);
	(close(pipe_fd[0]), close(pipe_fd[1]));
	(waitpid(pid[0], &status[0], 0), waitpid(pid[1], &status[1], 0));
	if (WIFSIGNALED(status[0]) && WTERMSIG(status[0]) == SIGPIPE)
		;
	else
		;
	return (WEXITSTATUS(status[1]));
}

static pid_t	pipe_cmd(t_data *data, t_ast *node, int fd, int pipe_fd[2])
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (perror("pipe fail"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
	{
		close(pipe_fd[fd]);
		if (dup2(pipe_fd[!fd], !fd) < 0)
			return (perror("dup2 failed"), 1);
		close(pipe_fd[!fd]);
		execute_node(data, node);
		del_lst(&data->env_llst);
		exit_cleanup(data);
	}
	return (pid);
}

//  set -o pipefail