
#include "../inc/minishell.h"

int		do_pipe_cmds(t_data *data, t_ast *node);

int		execute_pipe(t_data *data, t_ast *node)
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
// or can you just pass the ast node from data and save yourself some horizontal space
int		do_pipe_cmds(t_data *data, t_ast *node)
{
	int			fd[2];
	pid_t		pid;

	if (pipe(fd) == -1)
		; // piping failed, error and exit here
	pid = fork();
	if (pid == 0)
	{
		// child
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			; // exit function here
		execute_node(data, node->left);
		close(fd[1]);
	}
	else
	{
		// parent
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			; // exit
		execute_node(data, node->right);
		close(fd[0]);
		waitpid(pid, &data->exit_status, 0);
	}
	exit(WEXITSTATUS(data->exit_status));
}
