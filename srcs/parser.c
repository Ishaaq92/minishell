/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:19 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/25 16:14:39 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char **envp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	str++;
	while (envp[i] && ft_strncmp(envp[i], str, ft_strlen(str)) != 0)
		i ++;
	if (envp[i] == NULL)
		return (ft_strdup(""));
	while (envp[i][j] != '=')
		j ++;
	return (envp[i]+j+1);
}

void	parser(char *input, char *envp[])
{
	char	**strings;
	int		i;

	i = 0;
	strings = ft_split(input, ' ');
	while (strings[i] != 0)
	{
		// printf("%s\n", strings[i]);
		if (strings[i][0] == '$')
			printf("%s\n", expand_env(envp, strings[i]));
		free(strings[i]);
		i++;
	}
}