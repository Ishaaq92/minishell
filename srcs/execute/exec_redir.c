/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:21:46 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/27 16:44:14 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int				execute_redir(t_data *data, t_ast *node);
static int		redir_input(t_ast *node);
static int		redir_output(t_ast *node);
static int		check_file(t_token *token);
static int		redir_flags(enum e_type type);

// used to execute the redir node
// if there is a command, execute it after performing redirections
// then reset the std fds back to their original status
int	execute_redir(t_data *data, t_ast *node)
{
	param_sub(data, &node->right->token->literal, 0);
	remove_quotes(node->right->token->literal);
	if (check_file(node->token))
		return (1);
	if (node->type == REDIR_IN || node->type == IN_HEREDOC)
		data->exit_status = redir_input(node);
	else if (node->type == REDIR_OUT || node->type == OUT_APPEND)
		data->exit_status = redir_output(node);
	if (node->left && data->exit_status == 0)
		data->exit_status = execute_node(data, node->left);
	if (node->type == IN_HEREDOC)
		unlink(node->right->token->literal);
	return (reset_redir(data), data->exit_status);
}

static int	redir_input(t_ast *node)
{
	int		fd_redir;

	if (ft_isdigit(*node->token->literal))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = STDIN_FILENO;
	if (dup2(node->token->fd, fd_redir) == -1)
		return (perror("dup2 failed"), close_fd(&node->token->fd), 1);
	return (0);
}

// TODO: prevent double closes across minishell
static int	redir_output(t_ast *node)
{
	int		fd_redir;

	if (node->left == NULL)
		return (0);
	if (ft_isdigit(node->token->literal[0]))
		fd_redir = ft_atoi(node->token->literal);
	else
		fd_redir = STDOUT_FILENO;
	if (node->left == NULL)
		return (close_fd(&node->token->fd), 0);
	if (dup2(node->token->fd, fd_redir) == -1)
		return (perror("dup2 failed"), close_fd(&node->token->fd), 1);
	return (0);
}

// used to check if the file after redir in, out and append exists and can be
// written to
static int	check_file(t_token *token)
{
	DIR		*dir;

	dir = opendir(token->next->literal);
	if (dir)
		return (custom_error(token->next->literal, "Is a directory"),
			closedir(dir), 1);
	if (!token->next->literal || !*token->next->literal)
		return (custom_error("", "No such file or directory"),
			close_fd(&token->fd), 1);
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == OUT_APPEND)
	{
		token->fd = open(token->next->literal,
				redir_flags(token->type), 0666);
		if (access(token->next->literal, F_OK))
			return (custom_error(token->next->literal,
					"No such file or directory"), close_fd(&token->fd), 1);
		if (token->type == REDIR_IN && access(token->next->literal, R_OK))
			return (custom_error(token->next->literal,
					"Permission denied"), close_fd(&token->fd), 1);
		if (token->type != REDIR_IN && access(token->next->literal, W_OK))
			return (custom_error(token->next->literal,
					"Permission denied"), close_fd(&token->fd), 1);
	}
	return (0);
}

static int	redir_flags(enum e_type type)
{
	if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == OUT_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (type == REDIR_IN)
		return (O_RDONLY);
	return (0);
}
