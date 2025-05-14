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
	char	**env;
	int		i;

	i = 0;
	del_array(data->envp);
	data->envp = stitch_env(data->env_llst);
	env = data->envp;
	while (env && env[i] != NULL)
		printf("%s\n", env[i++]);
	data->exit_status = 0;
	return (0);
}

int	bi_unset(t_data *data, t_ast *node)
{
	remove_node(data, node->literal[1]);
	return (0);
}

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"'
int	bi_export(t_data *data, t_ast *node)
{
	char	*var;
	int		i;

	i = 1;
	var = node->literal[1];
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (bi_custom_error("export", var, "not an identifier"), 1);
	while (ft_isalnum(var[i]) || var[i] == '_' || var[i] == '=')
		i ++;
	if (var[i] != '\0')
		return (custom_error("export", "not an identifier"), 1);
	add_node(data, node->literal[1]);
	return (0);
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
