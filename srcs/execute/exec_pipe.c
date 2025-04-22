
#include "../inc/minishell.h"

int	do_pipe_cmds(t_ast *node, char **envp, t_envp *env_list);

int	execute_pipe(t_ast *node, char **envp, t_envp *env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		do_pipe_cmds(node, envp, env_list);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int	do_pipe_cmds(t_ast *node, char **envp, t_envp *env_list)
{
	int			fd[2];
	pid_t		pid;
	int			status;

	if (pipe(fd) == -1)
		; // piping failed, error and exit here
	pid = fork();
	if (pid == 0)
	{
		// child
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			; // exit function here
		execute_node(node->left, envp, env_list);
		close(fd[1]);
	}
	else
	{
		// parent
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			; // exit
		execute_node(node->right, envp, env_list);
		close(fd[0]);
		waitpid(pid, &status, 0);
	}
	exit(WEXITSTATUS(status));
}
