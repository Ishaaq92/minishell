/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/25 14:52:58 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// functions to build 
// echo: NOT DONE
// cd: NOT DONE
// unset: NOT DONE
// exit: NOT DONE
// export: ALMOST DONE
// env: TEST
// pwd: TEST

int	bi_cd(t_data *data)
{
	t_envp *lst;
	lst = data->env_llst;
}

char	*bi_pwd(t_data *data)
{
	char	**env;	
	int		i;

	i = 0;
	env = data->env_llst;
	while (env[i] != NULL && ft_strncmp(env[i], "pwd", 3) == 0)
		i++;
	if (env[i][4] == '=')
		return (value_envp(env[i], "pwd"));
	else if (env[i] == NULL)
		return (NULL);
}

void	bi_env(t_data *data)
{
	char	*env;
	int		i;

	i = 0;
	while (env[i] != NULL)
		printf("%s", env[i++]);
}

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"
void	bi_export(t_data *data, char *str)
{
	// Quote Removal.
	append_node(&data->head, &str, str);
}
