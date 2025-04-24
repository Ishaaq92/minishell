
#include "../inc/minishell.h"

int		execute_redir(t_data *data, t_ast *node);
int		redir_input(t_data *data, t_ast *node);
void	reset_redir(t_data *data);
int		redir_output(t_data *data, t_ast *node);

int	execute_redir(t_data *data, t_ast *node)
{
	// if fd is provided with the token atoi and set it as fd
	if (node->type == REDIRECT_IN)
		redir_input(data, node);
	else if (node->type == REDIRECT_OUT)
		redir_output(data, node);
	
	execute_node(data, node->left);
	dup2(data->std_fd[0], STDIN_FILENO);
	reset_redir(data);
	return (0);
}

int		redir_output(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;

	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 1;
	fd_newfile = open(node->right->token->literal, O_CREAT | O_WRONLY | O_TRUNC, 0666);
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
