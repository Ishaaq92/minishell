/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	export_empty_arg(t_data *data);
static int	is_key_valid(char *key);
static void	add_update_env(t_data *data, t_ast *node, int i);

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"'
int	bi_export(t_data *data, t_ast *node)
{
	int		i;
	int		error;

	if (node->literal[1] == NULL)
		return (export_empty_arg(data), 0);
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
static void	export_empty_arg(t_data *data)
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
		if (key[i] == '+' && key[i + 1] == '=')
			return (0);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (custom_error(key, "not a valid identifier"), 1);
		i++;
	}
	return (0);
}

static void	add_update_env(t_data *data, t_ast *node, int i)
{
	char	*key;
	char	*temp;
	t_envp	*existing;

	key = get_param_name(node->literal[i]);
	existing = check_envp(data, key);
	if (existing && ft_strchr(node->literal[i], '+'))
	{
		temp = existing->literal;
		existing->literal = ft_strjoin(existing->literal,
				ft_strchr(node->literal[i], '=') + 1);
		free(temp);
	}
	else if (existing && ft_strchr(node->literal[i], '='))
	{
		free(existing->literal);
		existing->literal = ft_strdup(node->literal[i]);
	}
	else
		add_node(data, node->literal[i]);
	free(key);
}
