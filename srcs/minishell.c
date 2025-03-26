/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/26 11:12:49 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char *envp[])
{
	char	*line;

	// if (ac == 2 && ft_strncmp(av[1], "clear", 5) == 0)
	// 	execve("/usr/bin/clear",)
	while (1)
	{
		handle_signals();
		line = readline("prompt: ");
		add_history(line);
		parser(line, envp);
	}
	return (0);
}
