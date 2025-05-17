/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/16 17:04:53 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Functions to Build 
// cd: NOT DONE
// echo: DONE
// exit: TESTING
// pwd: DONE
// export: ALMOST DONE
// env: DONE

static void	swap_dir(t_data *data);

int	echo_args(char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp("", str))
		return (1);
	if (str[i] == '-' && !str[i + 1])
		return (1);
	if (str[i++] != '-')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	bi_echo(t_data *data, t_ast *node)
{
	int		i;
	char	**args;

	(void) data;
	args = node->literal;
	if (args == NULL || args[1] == NULL)
		return (printf("\n"), 0);
	i = 1;
	while (args[i] && !echo_args(args[i]))
		i++;
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (echo_args(args[1]) == 1)
		printf("\n");
	return (0);
}

// check case with more than one argument passed into cd
int	bi_cd(t_data *data, t_ast *node)
{
	char	*new_path;
	char	*old_path;

	if (node->literal[1] == NULL || ft_strcmp(node->literal[1], "~") == 0)
		new_path = value_envp(&data->env_llst, "HOME");
	else if (ft_strcmp(node->literal[1], "-") == 0)
		return (swap_dir(data), 0);
	else
		new_path = ft_strdup(node->literal[1]);
	if (access(new_path, F_OK) == -1)
	{
		bi_custom_error("cd", node->literal[1], "No such file or directory");
		if (new_path)
			free(new_path);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (chdir(new_path) == -1)
		return(bi_custom_error("cd", node->literal[1], "Permission denied"), 1);
	env_alter(data, "OLDPWD=", old_path);
	if (old_path)
		free(old_path);
	env_alter(data, "PWD=", new_path);
	if (new_path)
		free(new_path);
	return (0);
}

static void	swap_dir(t_data *data)
{
	char	*old_path;
	char	*new_path;
	
	old_path = value_envp(&data->env_llst, "OLDPWD");
	new_path = value_envp(&data->env_llst, "PWD");
	if (old_path)
		chdir(old_path);
	env_alter(data, "OLDPWD=", new_path);
	env_alter(data, "PWD=", old_path);
	free(new_path);
	free(old_path);
}
