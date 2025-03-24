/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/24 15:01:41 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 
void	check_exec(char *str)
{
	char	**execs;
	int		i;

	while (execs[i] == 0)
	execs[0] = "echo";
	execs[1] = "pwd";
	execs[2] = "echo";
	execs[3] = "echo";
	execs[4] = "echo";
	execs[5] = "echo";
	execs[6] = "echo";
	execs[7] = "echo";
}
void	parser(char *input)
{
	char	**strings;
	int		i;

	i = 0;
	strings = ft_split(input, ' ');
	while (strings[i] != 0)
	{
		printf("%s\n", strings[i]);
		check_exec(strings[i]);
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