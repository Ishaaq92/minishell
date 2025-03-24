/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/24 15:47:19 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *input)
{
	char	**strings;
	int		i;

	i = 0;
	strings = ft_split(input, ' ');
	while (strings[i] != 0)
	{
		printf("%s\n", strings[i]);
		free(strings[i]);
		i++;
	}
}

int main(int ac, char *av[], char *envp[])
{
	char	*line;

	while (1)
	{
		line = readline("prompt: ");
		add_history(line);
		parser(line);
	}
	return (0);
}