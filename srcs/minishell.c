/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/23 17:46:33 by isahmed          ###   ########.fr       */
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
	handle_signals();
	int	i = 0;
	while (i < 1)		
	{
		line = readline("Prompt: ");
		if (*line)
		{	
			add_history(line);
			create_tokens(line, &head);
			ast = parse_tokens(head);
			print_ast(ast, 5);
			env_list = set_envp(envp);
			stitch_env(env_list);
			env_array = stitch_env(env_list);
			execute_node(ast, env_array, env_list);
			ft_lstclear(&head);
			free_ast(ast);
		}
		free(line);
		// i++;
	}
	return (0);
}
