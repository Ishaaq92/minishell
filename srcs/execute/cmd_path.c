/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 17:35:43 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-15 17:35:43 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_cmd_path(t_ast *node, t_envp *env_list)
{

	// if the given string is already a valid path
	if (access(node->literal[0], F_OK) == 0)
		return ;

}

void	execute_ast(t_ast *node, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		// child
		execve(node->literal[0], node->literal, envp);
	}
	else
	{
		// parent
		wait(NULL);
	}
}
