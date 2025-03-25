/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:22:13 by avalsang          #+#    #+#             */
/*   Updated: 2025/02/21 20:45:03 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_envp_paths(t_data *data, char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] != NULL)
	{
		envp[i] += 5;
		data->env_paths = ft_split(envp[i], ':');
	}
}

char	*set_path(char **cmds, t_data *data, int *i)
{
	char	*test_path;

	if (strncmp(cmds[0], ":", ft_strlen(cmds[0])) == 0)
		return (ft_strdup(":"));
	if (access(cmds[0], F_OK) == 0)
		test_path = ft_strdup(cmds[0]);
	else
		test_path = get_cmd_path(data, cmds[0]);
	if (test_path == NULL)
	{
		custom_error(cmds[0], "Command not found", 127, data);
		if (*i == data->argc - 2)
			data->last_cmd = 127;
		test_path = ft_strdup(cmds[0]);
	}
	return (test_path);
}

void	parse_cmds(int argc, char **argv, t_data *data)
{
	int		i;
	char	*test_path;
	char	**cmds;

	test_path = NULL;
	i = 2;
	while (i < argc - 1)
	{
		cmds = ft_split(argv[i], ' ');
		if (cmds == NULL || cmds[0] == NULL)
		{
			if (i == argc - 2)
				data->last_cmd = 127;
			cmds = ft_split(":", ' ');
		}
		test_path = set_path(cmds, data, &i);
		pipex_lstadd_back(&(data->cmd_list), pipex_lstnew(test_path, cmds));
		i++;
	}
}

char	*get_cmd_path(t_data *data, char *cmd)
{
	char	*temp;
	int		i;
	char	*test_path;

	i = 0;
	test_path = NULL;
	while (data->env_paths && data->env_paths[i])
	{
		temp = ft_strjoin(data->env_paths[i], "/");
		if (temp == NULL)
			return (NULL);
		test_path = ft_strjoin(temp, cmd);
		free(temp);
		if (test_path == NULL)
			return (NULL);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}
