/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 15:12:33 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-22 15:12:33 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	exec_cmd(t_data *data, char **argv, char **envp);
void	pipex(int fd[2], int *pid);
void	pipex_child(t_data *data, t_list *temp, char **argv, int fd[2]);
void	wait_for_children(int pid, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		return_code;

	if (argc < 5)
		return (1);
	data = malloc(sizeof(t_data));
	init_struct(data, argc);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc(argv[2], data);
		data->here_doc = 1;
		argc--;
		data->argc--;
		argv++;
	}
	else
		open_infile(data, argv);
	get_envp_paths(data, envp);
	parse_cmds(argc, argv, data);
	exec_cmd(data, argv, envp);
	if (data->last_cmd == 127)
		return (free_data(data), 127);
	return_code = data->error;
	return (free_data(data), WEXITSTATUS(return_code));
}

// check with ints if closes are working properly
void	exec_cmd(t_data *data, char **argv, char **envp)
{
	t_list	*temp;
	int		fd[2];
	int		pid;

	temp = data->cmd_list;
	if (dup2(data->in_fd, STDIN_FILENO) == -1)
		return (pipex_perror());
	close(data->in_fd);
	while (temp)
	{
		pipex(fd, &pid);
		if (pid == 0)
		{
			pipex_child(data, temp, argv, fd);
			execve(temp->path, temp->cmds, envp);
		}
		close(fd[1]);
		if (dup2(fd[0], 0) == -1)
			return (pipex_perror());
		close(fd[0]);
		temp = temp->next;
	}
	(close(data->out_fd), wait_for_children(pid, data));
}

void	pipex(int fd[2], int *pid)
{
	if (pipe(fd) == -1)
		return (pipex_perror());
	*pid = fork();
	if (*pid == -1)
		return (pipex_perror());
}

void	pipex_child(t_data *data, t_list *temp, char **argv, int fd[2])
{
	close(fd[0]);
	if (temp->next != NULL && dup2(fd[1], 1) == -1)
		pipex_perror();
	else if (temp->next == NULL)
	{
		init_outfile(data, data->argc, argv);
		if (dup2(data->out_fd, 1) == -1)
			pipex_perror();
		close(data->out_fd);
	}
	close(fd[1]);
	if (access(temp->path, X_OK) != 0)
		(free_data(data), exit(1));
}

void	wait_for_children(int pid, t_data *data)
{
	int	status;
	int	last;

	status = 0;
	last = 0;
	while (last != -1)
	{
		if (last == pid)
			data->error = status;
		last = waitpid(-1, &status, 0);
	}
}
