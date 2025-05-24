/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	echo_args(char *str);

int	bi_echo(t_data *data, t_ast *node)
{
	int		i;
	char	**args;

	(void) data;
	// signal(SIGPIPE, SIG_IGN);
	i = 0;

	args = node->literal;
	if (args == NULL || args[1] == NULL)
		return (printf("\n"), 0);
	i = 1;
	while (args[i] && !echo_args(args[i]))
		i++;
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (echo_args(args[1]) == 1)
		printf("\n");
	// signal(SIGPIPE, SIG_DFL);
	return (0);
}

static int	echo_args(char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp("", str))
		return (1);
	if (str[i] == '-' && !str[i + 1])
		return (1);
	if (str[i++] != '-')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}
