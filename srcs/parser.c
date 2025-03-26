/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:19 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/26 14:48:02 by isahmed          ###   ########.fr       */
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

void	skip_special_chars(char *str)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = 0;
	while (str[i] != 92 && str[i] != 59 && str[i] != '\0')
		i ++;
	if (str[i] != '\0')
		exit_cleanup();
	i = -1;
	while (str[++i] != '\0')
		if (str[i] == '"' || str[i] == '\'')
			quotes ++;
	if (quotes % 2 == 1)
		exit_cleanup();
}

void	parser(char *input, char *envp[])
{
	char	**strings;
	int		i;

	i = 0;
	// skip_special_chars(input);
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
