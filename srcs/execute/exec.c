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

int	execute_node(t_data *data, t_ast *node)
{
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

int	execute_logical(t_data *data, t_ast *node)
{
	data->exit_status = execute_node(data, node->left);
	if (node->type == LOGICAL_AND && data->exit_status == 0)
		data->exit_status = execute_node(data, node->right);
	else if (node->type == LOGICAL_OR && data->exit_status != 0)
		data->exit_status = execute_node(data, node->right);
	return (data->exit_status);
}
