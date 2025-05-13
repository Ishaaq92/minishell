/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:00:15 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/13 18:55:42 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_cleanup(t_data *data)
{
	int	exit_status;

	exit_status = data->exit_status;
	free_ast(data->head);
	del_lst(&data->env_llst);
	del_array(data->envp);
	ft_lstclear(&data->token_list);
	free(data);
	exit(exit_status);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}
