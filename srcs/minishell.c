/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/24 10:51:03 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	parser(char *input)
{
	printf("%s\n", input);
}


int main(int ac, char *av[], char *envp[])
{
	char	*line;

	while (1)
	{
		line = readline("prompt: ");
		add_history(line);
	}
	return (0);
}