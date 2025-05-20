/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_the_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_pwd(t_data *data)
{
	char	*pwd;

	(void) data;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	bi_env(t_data *data)
{
	t_envp	*temp;

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

int	ms_atoi(const char *str)
{
	size_t			i;
	int				minus;
	long int		result;

	i = 0;
	minus = 0;
	result = 0;
	while ((str[i] <= '\r' && str[i] >= '\t') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			minus = 1;
	}
	while (str[i])
		result = result * 10 + (str[i++] - '0');
	if (minus == 1)
		result = -result;
	if (result > INT_MAX || result < INT_MIN)
		return (custom_error("exit", "numeric argument required"), 1);
	return (result);
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
		if (args[1][0] == '+')
			j++;
		while (args[i][j] && ft_isdigit(args[i][j]) != 0)
			j++;
		if (args[1][0] == '\0' || (i == 1 && args[i][j] != '\0'))
			return (custom_error("exit", "numeric argument required"), 2);
		else if (i == 1 && args[i][j] == '\0' && j < 11)
			code = ms_atoi(args[i]);
	}
	if (i > 2)
		return (custom_error("exit", "too many arguments"), 1);
	data->exit_status = code % 256;
	exit_cleanup(data);
	return (0);
}
