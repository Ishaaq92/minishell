/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/09 22:58:42 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Functions to Build 
// cd: NOT DONE
// export: ALMOST DONE
// exit: TESTING
// echo: DONE
// env: DONE
// pwd: DONE

static void	swap_dir(t_data *data, t_ast *node);

int	echo_args(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}


void	bi_echo(t_data *data, t_ast *node)
{
	int		i;
	char	**args;

	args = node->literal;
	i = 1;
	while (!echo_args(args[i]))
		i++;
	if (args == NULL)
	{
		printf("\n");
		return ;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] && *args[i])
			printf(" ");
	}
	if (echo_args(args[1]) == 1)
		printf("\n");
}

// check case with more than one argument passed into cd
int	bi_cd(t_data *data, t_ast *node)
{
	char	*new_path;
	char	*old_path;

	if (node->literal[1] == NULL || ft_strcmp(node->literal[1], "~") == 0)
		new_path = value_envp(&data->env_llst, "HOME");
	else if (ft_strcmp(node->literal[1], "-") == 0)
		return (swap_dir(data, node), 0);
	else
		new_path = ft_strdup(node->literal[1]);
	if (access(new_path, F_OK) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", new_path);
		if (new_path)
			free(new_path);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (chdir(new_path) == -1)
		return(printf("path failed!\n"), 1);
	env_alter(data, "OLDPWD=", old_path);
	if (!old_path)
		free(old_path);
	env_alter(data, "PWD=", new_path);
	if (!new_path)
		free(new_path);
	return (0);
}


void	bi_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	bi_env(t_data *data)
{
	char	**env;
	int		i;

	i = 0;
	env = data->envp;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	data->exit_status = 0;
}

void	bi_unset(t_data *data, char *str)
{
	remove_node(&data->env_llst, str);
}

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"'
void	bi_export(t_data *data, char *str)
{
	add_node(data, str);
}

void	bi_exit(t_data *data)
{
	exit_cleanup(data);
}

static void	swap_dir(t_data *data, t_ast *node)
{
	char	*old_path;
	char	*new_path;
	
	old_path = value_envp(&data->env_llst, "OLDPWD");
	new_path = value_envp(&data->env_llst, "PWD");
	env_alter(data, "OLDPWD=", new_path);
	env_alter(data, "PWD=", old_path);
	free(new_path);
	free(old_path);
}