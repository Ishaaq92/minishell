/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/13 19:05:22 by isahmed          ###   ########.fr       */
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


int	bi_echo(t_data *data, t_ast *node)
{
	int		i;
	char	**args;

	args = node->literal;
	if (args == NULL || args[1] == NULL)
		return (printf("\n"), 0);
	i = 1;
	while (args[i] && !echo_args(args[i]))
		i++;
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] && *args[i])
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
		return (swap_dir(data, node), 0);
	else
		new_path = ft_strdup(node->literal[1]);
	if (access(new_path, F_OK) == -1)
	{
		cd_custom_error(node->literal[1], "No such file or directory");
		if (new_path)
			free(new_path);
		data->exit_status = 1;
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


int	bi_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

int	bi_env(t_data *data)
{
	int		i;
	t_envp	*temp;

	i = 0;
	temp = data->env_llst;
	while (temp != NULL)
	{
		printf("%s\n", temp->literal);
		temp = temp->next;
	}
	data->exit_status = 0;
}

int	bi_unset(t_data *data, t_ast *node)
{
	remove_node(&data->env_llst, node->literal[0]);
}

// export prints env with no args, each line preceded by "declare -x "
// to test, output bash and minishell into files, and use this cmd
//  sort ms.txt bash.txt | uniq -u 
void	export_empty_arg(t_data *data, t_ast *node)
{
	t_envp	*current;
	char	*key;
	char	*value;

	current = data->env_llst;
	while (current)
	{
		key = get_param_name(current->literal);
		value = value_envp(&data->env_llst, key);
		printf("declare -x %s", key);
		if (ft_strchr(current->literal, '='))
			printf("=\"%s\"", value);
		printf("\n");
		(free(key), free(value));
		current = current->next;
	}
}

int	is_key_valid(char *key)
{
	int		i;

	if (!ft_isalpha(key[0]))
		return (custom_error(key, "not a valid identifier"), 1);
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (custom_error(key, "not a valid identifier"), 1);
		i++;
	}
	return (0);
}

void	add_update_env(t_data *data, t_ast *node, int i)
{
	char	*key;
	t_envp	*existing;

	key = get_param_name(node->literal[i]);
	existing = check_envp(data, key);
	if (!ft_strchr(node->literal[i], '='))
	{
		if (existing)
		{
			free(existing->literal);
			existing->literal = ft_strdup(node->literal[i]);
		}
	}
	add_node(data, node->literal[i]);
	free(key);
}

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"'
int	bi_export(t_data *data, t_ast *node)
{
	int		i;
	int		error;

	if (node->literal[1] == NULL)
		return (export_empty_arg(data, node), 0);
	i = 1;
	error = 0;
	while (node->literal[i])
	{
		if (is_key_valid(node->literal[i]))
			error = 1;
		else
			add_update_env(data, node, i);
		i++;
	}
	return (error);
}

int	bi_exit(t_data *data, t_ast *node)
{
	char	**args;
	int		code;
	int		i;	
	int		j;	
	
	i = 0;
	code = 0;
	args = node->literal;
	while (args && args[0] && args[++i] != NULL)
	{
		j = 0;
		while (args[i][j] && ft_isdigit(args[i][j]) != 0)
			j++;
		if (i == 1 && args[i][j] != '\0')
			return (custom_error("exit","numeric argument required"), 2);
		else if (i == 1 && args[i][j] == '\0' && j < 11)
			code = ft_atoi(args[i]);
	}
	if (i > 2)
		return (custom_error("exit","too many arguments"), 1);
	data->exit_status = code;
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