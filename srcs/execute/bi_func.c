/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:08:06 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/06 14:22:43 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Functions to Build 
// echo: NOT DONE
// cd: NOT DONE
// export: ALMOST DONE
// exit: TESTING
// env: DONE
// pwd: DONE

void	bi_echo(t_data *data, t_ast *node)
{
	int		i;
	char	**args;

	// NEEDS QUOTE REMOVAL!
	args = node->literal;
	i = 1;
	if (args == NULL)
	{
		printf("\n");
		return ;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	printf("\n");
}

int	bi_cd(t_data *data, t_ast *node)
{
	char	*newdir;
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (chdir(node->literal[1]) == -1)
		printf("Bad Path\n");
	env_alter(data, "OLDPWD=", cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);	
	env_alter(data, "PWD=", cwd);
	free(cwd);
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
    remove_quotes(str);
    append_node(&data->env_llst, &str, str);
}

void	bi_exit(t_data *data)
{
	exit_cleanup(data);
}
