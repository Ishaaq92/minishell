/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/28 12:23:06 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Functions to Build 
// echo: NOT DONE
// cd: NOT DONE
// export: ALMOST DONE
// exit: TESTING
// unset: TESTING
// env: DONE
// pwd: DONE

int	bi_cd(t_data *data, t_ast *node)
{
	char	*newdir;
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (chdir(node->literal[1]) == -1)
		printf("Failure");
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
	remove_node(&data->env_llst, &data->envp, str);
}

// str must be the full string eg. 'pwd=/home/tim'
// str can be in the form 'pwd="/home/tim"'
void	bi_export(t_data *data, char *str)
{
	// Quote Removal.
	append_node(&data->env_llst, &str, str);
}

void	bi_exit(t_data *data)
{
	exit_cleanup(data);
}
