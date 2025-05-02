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

static char	*get_test_path(char *path, char *cmd_name);

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
		result = ft_split(env_list->literal + 5, ':');
		return (result);
	}
	return (NULL);
}

int	find_cmd_path(t_ast *node, t_envp *env_list)
{
	char	*test_path;
	char	**paths;
	int		i;

	if (access(node->literal[0], F_OK) == 0)
		return (0);
	paths = get_pathlist(env_list);
	i = 0;
	while (paths && paths[i])
	{
		test_path = get_test_path(paths[i], node->literal[0]);
		if (test_path == NULL)
			return (1);
		if (access(test_path, F_OK) == 0)
		{
			free(node->literal[0]);
			node->literal[0] = test_path;
			return (0);
		}
		free(test_path);
		i++;
	}
	return (perror(node->literal[0]), 1);
}

static char	*get_test_path(char *path, char *cmd_name)
{
	char	*temp;
	char	*test_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	test_path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (test_path);
}