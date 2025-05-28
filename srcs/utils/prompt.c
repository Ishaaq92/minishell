/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*exit_colour(int exit_status);

// function used to build the dynamic string before the readline prompt
char	*get_prompt(int exit_status)
{
	char	*prompt;
	char	*temp;
	char	*temp2;
	char	*pwd;

	temp = exit_colour(exit_status);
	temp2 = ft_itoa(exit_status);
	prompt = ft_strjoin(temp, temp2);
	(free(temp), free(temp2));
	temp = prompt;
	prompt = ft_strjoin(temp, " ]\001\e[0m\002 \001\e[0;94m\002");
	free(temp);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("why did you delete the directory you're in");
	temp2 = ft_strjoin(ft_strrchr(pwd, '/'), "\001\e[0m\002: ");
	temp = prompt;
	prompt = ft_strjoin(temp, temp2);
	return (free(temp), free(temp2), free(pwd), prompt);
}

// helper function for norm reasons. sets the colour based on exit no
// green if 0, red if 1, magenta for segfault, yellow for the rest
static char	*exit_colour(int exit_status)
{
	if (exit_status == 0)
		return (ft_strdup("\001\e[0;92m\002[ "));
	else if (exit_status == 1)
		return (ft_strdup("\001\e[0;91m\002[ "));
	else if (exit_status == 139)
		return (ft_strdup("\001\e[0;95m\002[ "));
	else
		return (ft_strdup("\001\e[0;93m\002[ "));
}
