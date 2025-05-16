/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: isahmed <isahmed@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/21 16:17:20 by isahmed		   #+#	#+#			 */
/*   Updated: 2025/04/25 17:37:41 by isahmed		  ###   ########.fr	   */
/*																			*/
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

# define BLUE "\e[0;34m"

// char	*join_and_free(char **s1, char **s2)
// {
// 	int		len;
// 	char	*result;

// 	len = ft_strlen(*s1) + ft_strlen(*s2);
// 	result = malloc()
// 	return (result);
// }

char	*exit_colour(int exit_status)
{
	if (!exit_status)
		return (ft_strdup("\e[1;34m[ "));
	else if (exit_status == 1)
		return (ft_strdup("\e[1;31m[ "));
	else if (exit_status == 139)
		return (ft_strdup("\e[1;35m[ "));
	else
		return (ft_strdup("\e[1;33m[ "));
}

char	*get_prompt(t_envp *env, int exit_status)
{
	char	*prompt;
	char	*temp;
	char	*temp2;

	temp = exit_colour(exit_status);
	temp2 = ft_itoa(exit_status);
	prompt = ft_strjoin(temp, temp2);
	free(temp), free(temp2);
	temp = prompt;
	prompt = ft_strjoin(temp, " ]\e[0m \e[1;36m");
	free(temp);
	while (ft_strncmp("PWD=", env->literal, 4))
		env = env->next;
	if (env)
		temp2 = ft_strjoin(env->literal + 4, "\e[0m: ");
	else
		temp2 = ft_strjoin("~", "\e[0m: ");
	temp = prompt;
	prompt = ft_strjoin(temp, temp2);
	return (free(temp), free(temp2), prompt);
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
			line = readline(prompt);
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

t_data	*init_exec_data(char **line, int *exit_status, t_envp *env_llst)
{
    t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->head = NULL;
	data->env_llst = env_llst;
	param_sub(data, line);
	if (create_tokens(*line, &(data->token_list)) || data->token_list == NULL)
	{
		*exit_status = 2;
		return (free_data(data), NULL);
	}
	// printf("\n***TOKEN LIST***\n");
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
