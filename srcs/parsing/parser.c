/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:19 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/26 14:54:06 by isahmed          ###   ########.fr       */
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
	int	double_quotes;

	quotes = 0;
	double_quotes = 0;
	i = 0;
	while (str[i] != 92 && str[i] != 59 && str[i] != '\0')
		i ++;
	if (str[i] != '\0')
		exit_cleanup();
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '"')
			double_quotes ++;
		else if (str[i] == '\'')
			quotes ++;
	}
	if (quotes % 2 == 1 || double_quotes % 2 == 1)
		exit_cleanup();
}

void	parser(char *input, char *envp[])
{
	char	**strings;
	int		i;

	i = 0;
	skip_special_chars(input);
	strings = ft_split2(input, " ");
	while (strings[i] != 0)
	{
		// printf("%s\n", strings[i]);
		if (strings[i][0] == '$')
			printf("%s\n", expand_env(envp, strings[i]));
		else if (ft_strncmp(strings[i], "pwd", 3) == 0)
			printf("%s\n", getcwd(NULL, 0));
		free(strings[i]);
		i++;
	}
}