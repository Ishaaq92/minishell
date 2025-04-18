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

char	**get_pathlist(t_envp *env_list)
{
	int		i;
	char	**result;

	i = 0;
	if (env_list == NULL)
		return (NULL);
	while (env_list && ft_strncmp(env_list->literal, "PATH=", 5) != 0)
		env_list = env_list->next;
	if (env_list != NULL)
	{
		env_list->literal += 5;
		result = ft_split(env_list->literal, ':');
		return (result);
	}
	return (NULL);
}


int	set_cmd_path(t_ast *node, t_envp *env_list)
{
	char	*temp;
	char	*test_path;
	char	**paths;
	int		i;

	// if the given string is already a valid path
	if (access(node->literal[0], F_OK) == 0)
		return (0);
	paths = get_pathlist(env_list);
	i = 0;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			return (1);
		test_path = ft_strjoin(temp, node->literal[0]);
		free(temp);
		if (test_path == NULL)
			return (1);
		if (access(test_path, F_OK) == 0)
		{
			temp = node->literal[0];
			node->literal[0] = test_path;
			free(temp);
			return (0);
		}
		free(test_path);
		i++;
	}
	printf("COMMAND NOT FOUND\n");
	return (1);
}

void	execute_ast(t_ast *node, char **envp, t_envp *env_list)
{
	int	pid;

	pid = fork();
	set_cmd_path(node, env_list);
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
