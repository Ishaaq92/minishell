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

t_data	*init_exec_data(char *line, char **envp, int *exit_status);
void	free_data(t_data *data);
void	testing(t_envp **lst);

void	ft_perror(void)
{
	perror("minishell: ");
}

void	custom_error(char *str, char *msg)
{
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_data	*data;
	int		exit_status;

	handle_signals();
	data = NULL;
	exit_status = 0;
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
	int fd = 0;

	if (isatty(fileno(stdin)))
	{
		while (42)
		{
			line = readline("Prompt: ");
			if (line && *line)
			{
				add_history(line);
				data = init_exec_data(line, envp, &exit_status);
				if (data == NULL)
					continue ;
				if (data)
					execute_node(data, data->head);
				exit_status = data->exit_status;
				free_data(data);
			}
			free(line);
		}
	}
	else
	{	
		line = get_next_line(fileno(stdin));
		while (line)
		{
			data = init_exec_data(ft_strtrim(line, "\n"), envp, &exit_status);
			if (data)
			{
				execute_node(data, data->head);
				exit_status = data->exit_status;
				free_data(data);
				free(line);
			}
			line = get_next_line(fileno(stdin));
		}
	}
	return (exit_status);
}

t_data	*init_exec_data(char *line, char **envp, int *exit_status)
{
	t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->head = NULL;
	data->envp = NULL;
	data->env_llst = NULL;
	if (create_tokens(line, &(data->token_list)) || data->token_list == NULL)
	{
		*exit_status = 2;
		return (free_data(data), NULL);
	}
	// printf("\n***TOKEN LIST***\n");
	// print_tokens(&(data->token_list));
	data->head = parse_tokens(data->token_list);
	// printf("\n*** AST TREE***\n");
	// print_ast(data->head, 3);
	data->env_llst = set_envp(envp);
	data->envp = stitch_env(data->env_llst);
	data->exit_status = *exit_status;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->std_fd[2] = dup(STDERR_FILENO);
	return (data);
}

t_data	*reset_data_struct(t_data *data)
{

}

void	free_data(t_data *data)
{
	// ft_lstclear(&data->token_list);
	// free_ast(data->head);
	exit_cleanup(data);
	// free(data);
}

void	testing(t_envp **lst)
{
	t_envp	*env_list;
	char	**env_array;
	char	str[8] = "ISHAAQ\0";

	env_list = *lst;
	env_array = stitch_env(env_list);
	print_envp(lst);
	printf("\n\n\n");
	// add_node(lst, env_array, str);
	print_envp(lst);
}
