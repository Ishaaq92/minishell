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
*/

/*
BUGS:
1. Execution breaks when a bad command name is given; stop forking and execve if a bad name is given
*/

void	free_data(t_data *data);
void	testing(t_envp **lst);

void	ft_perror()
{
	perror("minishell: ");
}

void	custom_error(char *str, char *msg)
{
	write(2, "pipex: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_data	*data;

	handle_signals();
	data = NULL;
	while (42)
	{
		line = readline("Prompt: ");
		if (line && *line)
		{
			add_history(line);
			data = init_exec_data(line, envp);
			if (data->head == NULL)
				continue ;
			printf("\n***COMMAND EXECUTION***\n");
			if (data)
				execute_node(data, data->head);
			free_data(data);
		}
		free(line);
	}
	return (0);
}

t_data	*init_exec_data(char *line, char **envp)
{
	t_data		*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	printf("\n***TOKEN LIST***\n");
	create_tokens(line, &(data->token_list));
	print_tokens(&(data->token_list));
	data->head = parse_tokens(data->token_list);
	printf("\n*** AST TREE***\n");
	print_ast(data->head, 3);
	data->env_llst = set_envp(envp);
	data->envp = stitch_env(data->env_llst);
	data->exit_status = 0;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->std_fd[2] = dup(STDERR_FILENO);
	return (data);
}

void	free_data(t_data *data)
{
	ft_lstclear(&data->token_list);
	free_ast(data->head);
	free(data);
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
