
#include "../inc/minishell.h"

int		execute_redir(t_data *data, t_ast *node);
int		redir_input(t_data *data, t_ast *node);
void	reset_redir(t_data *data);
int		redir_output(t_data *data, t_ast *node);
int		redir_heredoc(t_data *data, t_ast *node);

int		execute_redir(t_data *data, t_ast *node)
{
	// if fd is provided with the token atoi and set it as fd
	if (node->type == REDIRECT_IN)
		redir_input(data, node);
	else if (node->type == REDIRECT_OUT || node->type == REDIRECT_APPEND)
		redir_output(data, node);
	else if (node->type == REDIRECT_HEREDOC)
		redir_heredoc(data, node);
	execute_node(data, node->left);
	dup2(data->std_fd[0], STDIN_FILENO);
	reset_redir(data);
	if (node->type == REDIRECT_HEREDOC)
		unlink("temp");
	return (0);
}

int		redir_heredoc(t_data *data, t_ast *node)
{
	// int		fd[2];
	// pid_t	pid;

	// if (pipe(fd) < 0)
	// 	; // pipe failed, print error
	// pid = fork();
	// if (pid < 0)
	// 	; // forking failed, print error
	// if (pid == 0)
	// {
	// 	// child
	// 	// need signals here?
	// 	close(fd[0]);

	// }
	// else
	// {

	// }
	int		temp_fd;
	char	*buffer;
	char	*eof;

	// check limiter, make sure its not null
	// if (lim) {}
	temp_fd = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	eof = node->right->token->literal;
	if (temp_fd < 0)
		; // print error
	while (42)
	{
		write(1, "> ", 2);
		buffer = get_next_line(0);
		if (buffer == NULL)
			break ;
		if (ft_strncmp(buffer, eof, ft_strlen(buffer) - 1) == 0)
			break ;
		(write(temp_fd, buffer, ft_strlen(buffer)), free(buffer));
	}
	(free(buffer));
	close(temp_fd);
	temp_fd = open("temp", O_RDONLY);
	if (dup2(temp_fd, STDIN_FILENO))
		; // print error
	// close(STDIN_FILENO);
	return (0);
}

int		redir_output(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;
	int		flag;

	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 1;
	if (node->type == REDIRECT_OUT)
		flag = O_TRUNC;
	else
		flag = O_APPEND;
	fd_newfile = open(node->right->token->literal, O_CREAT | O_WRONLY | flag, 0666);
	// printf("filename = %s, fd = %i\n", node->right->token->literal, fd_newfile);
	if (fd_newfile < 0)
		; // couldn't create a new file, return error
	if (dup2(fd_newfile, fd_redir) == -1)
		; // failed dup2, print error and exit
	return (0);
}

// TODO: fix the line with three arrows, put the filename in a 
// more accessible location
int		redir_input(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;

	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 0;
	fd_newfile = open(node->right->token->literal, O_RDONLY);
	// printf("filename = %s, fd = %i\n", node->right->token->literal, fd_newfile);
	if (fd_newfile < 0)
		; // couldn't create a new file, return error
	if (dup2(fd_newfile, fd_redir) == -1)
		; // failed dup2, print error and exit
	return (0);
}

void	reset_redir(t_data *data)
{
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
	dup2(data->std_fd[2], STDERR_FILENO);
}
