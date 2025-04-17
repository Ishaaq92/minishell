/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/17 20:59:50 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	testing(t_envp **lst)
{
	t_envp	*env_list;
	char	**env_array;

	env_list = *lst;
	char	str[8] = "PWD\0";
	// printf("%s\n", str);
	// printf("%s\n", value_envp(&env_list, str));
	// printf("%zu\n", ft_strlen(value_envp(&env_list, str)));
	// printf("%s\n", value_envp(&env_list, str));
	print_envp(&env_list);
	env_array = stitch_env(env_list);
	printf("\n\n");
	remove_node(lst, &env_array, str);
	printf("\n\n");
	int	i = 0;
	while (env_array[i] != NULL)
		printf("%s\n", env_array[i++]);
}

int main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_token	*head;
	t_ast	*ast;
	t_envp	*env_list;
	char	**env_array;

	head = NULL;
	int	i = 0;
	handle_signals();
	while (i < 1)		
	{
		line = readline("prompt: ");
		add_history(line);
		// parser(line, envp);
		create_tokens(line, &head);
		ast = parse_tokens(head);
		print_ast(ast, 5);
		env_list = set_envp(envp);
		stitch_env(env_list);
		testing(&env_list);
		// env_array = stitch_env(env_list);
		// execute_ast(ast, env_array);
		ft_lstclear(&head);
		free(line);
		free_ast(ast);
		i++;
	}
	return (0);
}
