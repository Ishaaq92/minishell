/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:52:48 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/21 19:40:07 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ms_start(char **line, t_envp *env_llst, int *exit_status);
static int	ms_readline(char **line, int *exit_status);

int	main(int ac, char *av[], char *envp[])
{
	char		*line;
	int			exit_status;
	t_envp		*env_llst;

	handle_signals();
	env_llst = NULL;
	exit_status = 0;
	(void) ac;
	(void) av;
	if (isatty(fileno(stdin)))
	{
		env_llst = set_envp(envp);
		while (42)
		{
			ms_start(&line, env_llst, &exit_status);
			if (!line)
				break ;
		}
	}
	return (del_lst(&env_llst), exit_status);
}

static int	ms_readline(char **line, int *exit_status)
{
	char		*prompt;

	rl_erase_empty_line = 0;
	prompt = get_prompt(*exit_status);
	(*line) = readline(prompt);
	free(prompt);
	if (get_signal() == SIGINT)
	{
		set_signal(0);
		*exit_status = 130;
		if (*line)
			free(*line);
		return (1);
	}
	return (0);
}

static int	ms_start(char **line, t_envp *env_llst, int *exit_status)
{
	t_data		*data;

	data = NULL;
	if (ms_readline(line, exit_status))
		return (1);
	if ((*line) && (**line))
	{
		data = parse_line(line, exit_status, env_llst);
		add_history(*line);
		if (data)
		{
			execute_node(data, data->head);
			*exit_status = data->exit_status;
			env_llst = data->env_llst;
		}
		(free_data(data), free(*line));
	}
	else if (!(*line))
		return (1);
	return (0);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->head)
		free_ast(data->head);
	if (data->token_list)
		ft_lstclear(&data->token_list);
	reset_redir(data);
	close_fd(&data->std_fd[0]);
	close_fd(&data->std_fd[1]);
	close_fd(&data->std_fd[2]);
	free(data);
}
