/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		execute_redir(t_data *data, t_ast *node);
static int		redir_input(t_data *data, t_ast *node);
static int		redir_output(t_data *data, t_ast *node);
void	reset_redir(t_data *data);

int	execute_redir(t_data *data, t_ast *node)
{
	if (node->type != IN_HEREDOC)
	{
		param_sub(data, &node->right->token->literal);
		remove_quotes(node->right->token->literal);
	}
	if (node->type == REDIR_IN || node->type == IN_HEREDOC)
		data->exit_status = redir_input(data, node);
	else if (node->type == REDIR_OUT || node->type == OUT_APPEND)
		data->exit_status = redir_output(data, node);
	if (node->left && data->exit_status == 0)
		execute_node(data, node->left);
	reset_redir(data);
	if (node->type == IN_HEREDOC)
		unlink(node->right->literal[0]);
	return (data->exit_status);
}

static int	redir_input(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;

	(void) data;
	if (ft_isdigit(*node->token->literal))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 0;
	fd_newfile = open(node->right->literal[0], O_RDONLY);
	if (fd_newfile < 0)
		return (custom_error(node->right->literal[0],
				"No such file or directory"), 1);
	if (dup2(fd_newfile, fd_redir) == -1)
		return (perror("dup2 failed"), 1);
	close(fd_newfile);
	return (0);
}

static int	redir_output(t_data *data, t_ast *node)
{
	int		fd_newfile;
	int		fd_redir;
	int		flags;

	(void) data;
	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = 1;
	if (node->type == REDIR_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd_newfile = open(node->right->literal[0], flags, 0666);
	if (fd_newfile < 0)
		return (custom_error(node->right->literal[0],
				"No such file or directory"), 1);
	if (dup2(fd_newfile, fd_redir) == -1)
		return (perror("dup2 failed"), 1);
	close(fd_newfile);
	return (0);
}

void	reset_redir(t_data *data)
{
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
	dup2(data->std_fd[2], STDERR_FILENO);
}
