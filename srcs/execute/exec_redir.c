/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:21:28 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 16:21:28 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		execute_redir(t_data *data, t_ast *node);
int		redir_input(t_data *data, t_ast *node);
void	reset_redir(t_data *data);
int		redir_output(t_data *data, t_ast *node);
int		redir_heredoc(t_data *data, t_ast *node);

int	execute_redir(t_data *data, t_ast *node)
{
	// clean_args(data, node);
	if (node->type != IN_HEREDOC)
	{
		param_sub(data, &node->right->token->literal);
		remove_quotes(node->right->token->literal);
	}
	if (node->type == REDIR_IN)
		data->exit_status = redir_input(data, node);
	else if (node->type == REDIR_OUT || node->type == OUT_APPEND)
		data->exit_status = redir_output(data, node);
	else if (node->type == IN_HEREDOC)
		data->exit_status = redir_heredoc(data, node);
	if (node->left && data->exit_status == 0)
		execute_node(data, node->left);
	dup2(data->std_fd[0], STDIN_FILENO);
	reset_redir(data);
	if (node->type == IN_HEREDOC)
		unlink("temp");
	return (data->exit_status);
}

// cat needs the fd to have RDONLY flag I think? look it up TODO
int	redir_heredoc(t_data *data, t_ast *node)
{
	int		temp_fd;
	char	*buffer;
	char	*eof;

	temp_fd = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	eof = node->right->token->literal;
	if (temp_fd < 0)
		ft_perror();
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
	(free(buffer), close(temp_fd));
	temp_fd = open("temp", O_RDONLY);
	if (dup2(temp_fd, STDIN_FILENO))
		;
	return (0);
}

int	redir_output(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;
	int		flag;

	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 1;
	if (node->type == REDIR_OUT)
		flag = O_TRUNC;
	else
		flag = O_APPEND;
	fd_newfile = open(node->right->token->literal,
			O_CREAT | O_WRONLY | flag, 0666);
	if (fd_newfile < 0)
	{
		custom_error(node->right->token->literal, "No such file or directory");
		return (1);
	}
	if (dup2(fd_newfile, fd_redir) == -1)
		;
	return (0);
}

// TODO: fix the line with three arrows, put the filename in a 
// more accessible location
int	redir_input(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;

	if (ft_isdigit(*node->token->literal))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 0;
	fd_newfile = open(node->right->token->literal, O_RDONLY);
	if (fd_newfile < 0)
	{
		custom_error(node->right->token->literal, "No such file or directory");
		return (1);
	}
	if (dup2(fd_newfile, fd_redir) == -1)
		;
	return (0);
}

void	reset_redir(t_data *data)
{
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
	dup2(data->std_fd[2], STDERR_FILENO);
}
