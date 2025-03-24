/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/21 17:11:59 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	parser(char *input)
{
	printf("%s\n", input);
}


int main(int ac, char *av[], char *envp[])
{
	int i;

	// i = 0;
	// while (envp[i] != 0)
	// 	printf("%s\n", envp[i++]);
	while (1)
	{
		parser(readline("prompt: "));
	}
	return (0);
}