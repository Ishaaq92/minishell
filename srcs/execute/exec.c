/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:21:46 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 16:21:46 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_builtin(t_data *data, t_ast *node);
int		execute_logical(t_data *data, t_ast *node);

// used to redirect the node to the correct exec function
// also kickstarts the execution process, each ast node will call
// back to this function until no nodes are left
int	execute_node(t_data *data, t_ast *node)
{
	if (data == NULL || node == NULL)
		return (0);
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		data->exit_status = execute_logical(data, node);
	else if (node->type == PIPE)
		data->exit_status = execute_pipe(data, node);
	else if (node->type > 1 && node->type < 6)
		data->exit_status = execute_redir(data, node);
	else if (node->type == WORD)
		data->exit_status = execute_cmd(data, node);
	return (data->exit_status);
}

// executes the logical nodes
// && operator only executes the next cmd if exit code was 0
// || only executes next cmd if exit code was not 0
int	execute_logical(t_data *data, t_ast *node)
{
	data->exit_status = execute_node(data, node->left);
	if (node->type == LOGICAL_AND && data->exit_status == 0)
		data->exit_status = execute_node(data, node->right);
	else if (node->type == LOGICAL_OR && data->exit_status != 0)
		data->exit_status = execute_node(data, node->right);
	return (data->exit_status);
}
