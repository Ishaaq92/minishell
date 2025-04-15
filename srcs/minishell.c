/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:17:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/15 17:26:35 by isahmed          ###   ########.fr       */
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

int main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_token	*head;
	t_ast	*ast;
	t_envp	*env_list;

	head = NULL;
	int	i = 0;
	printf("%ld", sizeof(char *));
	while (i < 1)
	{
		handle_signals();
		line = readline("prompt: ");
		add_history(line);
		// parser(line, envp);
		// create_tokens(line, &head);
		// ast = parse_tokens(head);
		// print_ast(ast, 5);
		env_list = set_envp(envp);
		stitch_env(env_list);
		// ft_lstclear(&head);
		// free(line);
		// free_ast(ast);
		i++;
	}
	return (0);
}
