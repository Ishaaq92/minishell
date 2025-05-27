/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/27 18:19:45 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	swap_dir(t_data *data);
static char	*more_bi_cd(t_data *data, t_ast *node);
static void	change_wd(t_data *data, char *new_path, char *old_path);

// check case with more than one argument passed into cd
int	bi_cd(t_data *data, t_ast *node)
{
	char	*new_path;
	char	*old_path;

	if (node->literal[1] && ft_strcmp(node->literal[1], "-") == 0)
		return (swap_dir(data));
	new_path = more_bi_cd(data, node);
	if (!new_path)
		return (bi_custom_error("cd", "HOME", "not set"), 1);
	if (access(new_path, F_OK) == -1)
	{
		bi_custom_error("cd", new_path, "No such file or directory");
		if (new_path)
			free(new_path);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (chdir(new_path) == -1)
		return (bi_custom_error("cd", new_path, "Permission denied"),
			free(new_path), free(old_path), 1);
	change_wd(data, new_path, old_path);
	return (0);
}

static int	swap_dir(t_data *data)
{
	char	*old_path;
	char	*new_path;

	old_path = value_envp(&data->env_llst, "OLDPWD");
	if (!old_path)
		return (custom_error("cd", "OLDPWD not set" ), 1);
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (custom_error("cd", "getcwd failed" ), 1);
	if (old_path)
	{
		chdir(old_path);
		env_alter(data, "OLDPWD=", new_path);
		env_alter(data, "PWD=", old_path);
	}
	printf("%s\n", old_path);
	(free(new_path), free(old_path));
	return (0);
}

static char	*more_bi_cd(t_data *data, t_ast *node)
{
	char	*new_path;

	if (node->literal[1] == NULL
		|| !ft_strcmp(node->literal[1], "~")
		|| !ft_strcmp(node->literal[1], "--"))
		new_path = value_envp(&data->env_llst, "HOME");
	else
		new_path = ft_strdup(node->literal[1]);
	return (new_path);
}

static void	change_wd(t_data *data, char *new_path, char *old_path)
{
	char	*temp;

	env_alter(data, "OLDPWD=", old_path);
	if (old_path)
		free(old_path);
	temp = getcwd(NULL, 0);
	if (temp)
		(env_alter(data, "PWD=", temp), free(temp));
	if (new_path)
		free(new_path);
}
