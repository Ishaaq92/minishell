/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/17 16:02:04 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free((*lst)->literal);
			free((*lst));
			(*lst) = tmp;
		}
	}
}

void	testing(t_envp **lst)
{
	t_envp	*env_list;
	char	**env_array;
	int		i;

	i = 0;
	env_list = *lst;
	char	str[8] = "SHELL\0";
	// printf("%s\n", str);
	// printf("%s\n", value_envp(&env_list, str));
	// printf("%zu\n", ft_strlen(value_envp(&env_list, str)));
	// printf("%s\n", value_envp(&env_list, str));
	print_envp(&env_list);
	env_array = stitch_env(env_list);
	printf("\n\n");
	remove_node(lst, env_array, str);
	print_envp(&env_list);
	// printf("%s\n", value_envp(&env_list, str));
}

int main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_token	*head;
	t_ast	*ast;
	t_envp	*env_list;
	char	**env2;

	head = NULL;
	int	i = 0;
	while (i < 1)		
	{
		handle_signals();
		line = readline("prompt: ");
		add_history(line);
		// parser(line, envp);
		create_tokens(line, &head);
		ast = parse_tokens(head);
		print_ast(ast, 5);
		env_list = set_envp(envp);
		stitch_env(env_list);
		testing(&env_list);
		// ft_lstclear(&head);
		// free(line);
		// free_ast(ast);
		i++;
		env2 = stitch_env(env_list);
		execute_ast(ast, env2);
		ft_lstclear(&head);
		free(line);
		free_ast(ast);
		// i++;
	}
	return (0);
}
