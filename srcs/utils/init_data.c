/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 13:05:29 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-27 13:05:29 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		create_ast(t_data *data, int *exit_status);
static t_data	*init_data(void);

t_data	*parse_line(char **line, int *exit_status, t_envp **env_llst)
{
	t_data		*data;

	data = init_data();
	if (!data)
		return (NULL);
	data->env_llst = *env_llst;
	create_tokens(*line, &(data->token_list));
	if (!data->token_list)
		return (free_data(data), NULL);
	if (create_ast(data, exit_status))
		return (ft_lstclear(&data->token_list), free_data(data), NULL);
	return (data);
}

static int	create_ast(t_data *data, int *exit_status)
{
	if (data->token_list && check_valid_order(&data->token_list))
	{
		*exit_status = 2;
		return (custom_error("tokens", "syntax error"), 1);
	}
	if (parse_heredoc(data, data->token_list))
	{
		*exit_status = get_signal() + 128;
		return (set_signal(0), 1);
	}
	else
		data->exit_status = *exit_status;
	wildcards(data);
	data->head = parse_tokens(data->token_list);
	return (0);
}

static t_data	*init_data(void)
{
	t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->head = NULL;
	data->env_llst = NULL;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->std_fd[2] = dup(STDERR_FILENO);
	return (data);
}
