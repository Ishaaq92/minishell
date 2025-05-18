/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 13:52:48 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 13:52:48 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_data	*init_exec_data(char **line, int *exit_status, t_envp *env_llst);
void	free_data(t_data *data);

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
// 			data = init_exec_data(&line2, &exit_status, env_llst);
// 			if (data)
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

int	main(int ac, char *av[], char *envp[])
{
	char	*line;
	char	*prompt;
	t_data	*data;
	int		exit_status;
	t_envp	*env_llst;

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
			prompt = get_prompt(exit_status);
			line = readline(prompt);
			free(prompt);
			if (line && *line)
			{
				add_history(line);
				data = init_exec_data(&line, &exit_status, env_llst);
				if (data == NULL)
					continue ;
				if (data)
					execute_node(data, data->head);
				exit_status = data->exit_status;
				env_llst = data->env_llst;
				free_data(data);
			}
			free(line);
		}
	}
	// tester only
	else
	{	
		env_llst = set_envp(envp);
		line = get_next_line(fileno(stdin));
		while (line)
		{
			char *line2 = ft_strtrim(line, "\n");
			data = init_exec_data(&line2, &exit_status, env_llst);
			if (data)
			{
				execute_node(data, data->head);
				exit_status = data->exit_status;
				env_llst = data->env_llst;
				free_data(data);
				free(line);
			}
			line = get_next_line(fileno(stdin));
		}
	}
	return (del_lst(&env_llst), exit_status);
}

static t_data	*init_exec_data(char **line, int *exit_status, t_envp *env_llst)
{
    t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->head = NULL;
	data->env_llst = env_llst;
	create_tokens(*line, &(data->token_list));
	// if () || data->token_list == NULL)
	if (data->token_list && check_valid_order(&data->token_list))
	{
		*exit_status = 2;
		return (custom_error("tokens", "syntax error"), free_data(data), NULL);
	}
	// printf("\n***TOKEN LIST***\n");
	// param_sub(data, line);
	// clean_args(data);
	wildcards(data);
	// print_tokens(& 	(data->token_list));
	data->head = parse_tokens(data->token_list);
	// printf("\n*** AST TREE***\n");
	// print_ast(data->head, 3);
	data->exit_status = *exit_status;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->std_fd[2] = dup(STDERR_FILENO);
	// close(data->std_fd[0]);
	// close(data->std_fd[1]);
	// close(data->std_fd[2]);
	return (data);
}

void	free_data(t_data *data)
{
	free_ast(data->head);
	// del_lst(&data->env_llst);
	ft_lstclear(&data->token_list);
	free(data);
	// exit_cleanup(data);
}

	// if (ac >= 2 && !ft_strncmp(av[1], "-c", 2))
	// if (ac > 1)
	// {
	// 	data = init_exec_data(ft_strtrim(get_next_line(fileno(stdin)), "\n"), envp, &exit_status);
	// 	if (data)
	// 	{
	// 		execute_node(data, data->head);
	// 		exit_status = data->exit_status;
	// 		free_data(data);
	// 	}
	// 	return (exit_status);
	// }
	// int fd = 0;