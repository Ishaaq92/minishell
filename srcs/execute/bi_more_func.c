/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_more_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:16:31 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/14 17:17:39 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	export_empty_arg(t_data *data, t_ast *node);
static int	is_key_valid(char *key);
static void	add_update_env(t_data *data, t_ast *node, int i);

int	bi_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
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
	return (0);
}

int	bi_unset(t_data *data, t_ast *node)
{
	int		i;

	i = 0;
	while (node->literal[++i])
		if (node->literal[i])
			remove_node(data, node->literal[i]);
	return (0);
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

// export prints env with no args, each line preceded by "declare -x "
// to test, output bash and minishell into files, and use this cmd
//  sort ms.txt bash.txt | uniq -u 
static void	export_empty_arg(t_data *data, t_ast *node)
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

static int	is_key_valid(char *key)
{
	int		i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
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

static void	add_update_env(t_data *data, t_ast *node, int i)
{
	char	*key;
	t_envp	*existing;

	key = get_param_name(node->literal[i]);
	existing = check_envp(data, key);
	if (existing && ft_strchr(node->literal[i], '='))
	{
			free(existing->literal);
			existing->literal = ft_strdup(node->literal[i]);
	}
	else
		add_node(data, node->literal[i]);
	free(key);
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
	// Will never return 0
	return (0);
}
