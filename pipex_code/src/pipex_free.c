/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:39:34 by abhi              #+#    #+#             */
/*   Updated: 2025/02/21 19:51:59 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
	}
	free(arr);
}

void	free_data(t_data *data)
{
	t_list	*tmp;

	if (data->here_doc == 1)
		unlink("temp");
	free_array(data->env_paths);
	while (data->cmd_list != NULL)
	{
		tmp = data->cmd_list;
		data->cmd_list = data->cmd_list->next;
		free_array(tmp->cmds);
		free(tmp->path);
		free(tmp);
	}
	free(data);
}
