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

#include "minishell.h"

/*
TODO:
1. Exit status
2. Built in functions
3. Parameter substitution with quote removal
4. Signals
5. Compiler flags, DO NOT FORGET
*/

t_data	*init_exec_data(char **line, int *exit_status, t_envp *env_llst);
void	free_data(t_data *data);
void	testing(t_envp **lst);

void	ft_perror(void)
{
    perror("minishell: ");
}

int	bi_custom_error(char * func, char *str, char *msg)
{
    write(2, "minishell: ", 12);
    write(2, func, ft_strlen(func));
    write(2, ": ", 2);
    write(2, str, ft_strlen(str));
    write(2, ": ", 2);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (0);
}

int	custom_error(char *str, char *msg)
{
    write(2, "minishell: ", 12);
    write(2, str, ft_strlen(str));
    write(2, ": ", 2);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (0);
}


char	*exit_colour(int exit_status)
{
	if (!exit_status)
		return (ft_strdup("\001\e[0;92m\002[ "));
	else if (exit_status == 1)
		return (ft_strdup("\001\e[0;91m\002[ "));
	else if (exit_status == 139)
		return (ft_strdup("\001\e[0;95m\002[ "));
	else
		return (ft_strdup("\001\e[0;93m\002[ "));
}

// char	*join_and_free(char **s1, char **s2)
// {
// 	int		len;
// 	char	*result;

// 	len = ft_strlen(*s1) + ft_strlen(*s2);
// 	// result = malloc()
// 	// return (result);
// }

char	*set_prompt(int n, ...)
{
	va_list		args;
	char		*temp;
	char		*arg;
	char		*result;
	int			i;

	i = 0;
	va_start(args, n);
	result = ft_strdup("");
	while (i++ < n)
	{
		arg = (char *)va_arg(args, char *);
		temp = result;
		result = ft_strjoin(temp, arg);
		free(temp);
	}
	return (va_end(args), result);
}

# define BLUE "\001\e[0;94m\002"

char	*get_prompt(t_envp *env, int exit_status)
{
	char	*colour;
	char	*exit_str;
	char	*pwd;
	char	*result;

	colour = exit_colour(exit_status);
	exit_str = ft_itoa(exit_status);
	while (ft_strncmp("PWD=", env->literal, 4))
		env = env->next;
	if (env)
		pwd = ft_strjoin(env->literal + 4, "\001\e[0m\002: ");
	else
		pwd = ft_strdup("~\001\e[0m\002: ");
	result = set_prompt(4, colour, exit_str, " ]\001\e[0m\002 {BLUE}", pwd);
	return (free(colour), free(exit_str), free(pwd), result);
}

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

	if (isatty(fileno(stdin)))
	{
		env_llst = set_envp(envp);
		while (42)
		{
			prompt = get_prompt(env_llst, exit_status);
			(void)prompt;
			rl_end = 10;
			line = readline(prompt);
			printf("rlpoint %i\n", rl_mark);
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
			free(line), free(prompt);
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

t_data	*init_exec_data(char **line, int *exit_status, t_envp *env_llst)
{
    t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->head = NULL;
	data->env_llst = env_llst;
	if (create_tokens(*line, &(data->token_list)) || data->token_list == NULL)
	{
		*exit_status = 2;
		return (free_data(data), NULL);
	}
	// printf("\n***TOKEN LIST***\n");
	param_sub(data, line);
	clean_args(data);
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
