/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/17 21:33:02 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	testing(t_envp **lst)
{
	t_envp	*env_list;
	char	**env_array;

	env_list = *lst;
	env_array = stitch_env(env_list);
	char	str[8] = "ISHAAQ\0";
    print_envp(lst);
    printf("\n\n\n");
	append_node(lst, env_array, str);
    print_envp(lst);
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
		// testing(&env_list);
		env_array = stitch_env(env_list);
		execute_ast(ast, env_array, env_list);
		ft_lstclear(&head);
		free(line);
		free_ast(ast);
		// i++;
	}
	return (0);
}
