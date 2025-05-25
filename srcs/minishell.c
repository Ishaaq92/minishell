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

static t_data	*parse_line(char **line, int *exit_status, t_envp *envlst);
static int		create_ast(t_data *data, int *exit_status);
static t_data	*init_data(void);
void			free_data(t_data *data);

int	main(int ac, char *av[], char *envp[])
{
	char		*line;
	char		*prompt;
	t_data		*data;
	int			exit_status;
	t_envp		*env_llst;

	handle_signals();
	data = NULL;
	env_llst = NULL;
	exit_status = 0;
	(void) ac;
	(void) av;
	if (isatty(fileno(stdin)))
	{
		env_llst = set_envp(envp);
		while (42)
		{
			rl_erase_empty_line = 0;
			prompt = get_prompt(exit_status);
			line = readline(prompt);
			free(prompt);
			if (get_signal() == SIGINT)
			{
				set_signal(0);
				exit_status = 130;
				if (line && *line)
					free(line);
				continue ;
			}
			if (line && *line)
			{
				data = parse_line(&line, &exit_status, env_llst);
				add_history(line);
				if (data)
				{
					execute_node(data, data->head);
					exit_status = data->exit_status;
					env_llst = data->env_llst;
				}
				free_data(data);
				free(line);
			}
			else if (!line)
			{
				del_lst(&env_llst);
				break ;
			}
		}
	}
	else
	{
		env_llst = set_envp(envp);
		line = get_next_line(fileno(stdin));
		while (line)
		{
			char *line2 = ft_strtrim(line, "\n");
			data = parse_line(&line2, &exit_status, env_llst);
			if (data)
			{
				execute_node(data, data->head);
				exit_status = data->exit_status;
				env_llst = data->env_llst;
				free_data(data);
			}
			(free(line), free(line2));
			line = get_next_line(fileno(stdin));
		}
	}
	return (del_lst(&env_llst), exit_status);
}

static t_data	*parse_line(char **line, int *exit_status, t_envp *envlst)
{
	t_data		*data;

	data = init_data();
	if (!data)
		return (NULL);
	data->env_llst = envlst;
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

// int	main(int ac, char *av[], char *envp[])
// {
// 	char	*line;
// 	t_data	*data;
// 	int		exit_status;
// 	t_envp	*env_llst;

// 	handle_signals();
// 	data = NULL;
// 	env_llst = NULL;
// 	exit_status = 0;
// 	(void) ac;
// 	(void) av;
// 	{	
// 		int testfd = open("test.sh", O_RDONLY);
// 		env_llst = set_envp(envp);
// 		line = get_next_line(testfd);
// 		while (line)
// 		{
// 			char *line2 = ft_strtrim(line, "\n");
// 			data = parse_line(&line2, &exit_status, env_llst);
// 			if (data && data->head)
// 			{
// 				execute_node(data, data->head);
// 				exit_status = data->exit_status;
// 				env_llst = data->env_llst;
// 				free_data(data);
// 				free(line);
// 			}
// 			line = get_next_line(testfd);
// 		}
// 	}
// 	return (del_lst(&env_llst), exit_status);
// }
