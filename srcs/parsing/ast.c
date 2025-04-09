/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:56:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/07 18:20:02 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*ast_new(enum e_type type)
{
	t_ast *new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->left = NULL;
	new->right = NULL;
	new->literal = NULL;
	new->parent = NULL;
	new->type = type;
	return (new);
}

int	count_argc(t_token *node)
{
	t_token *temp;
	int		count;

	count = 0; // start counting at 1?
	temp = node;
	while (temp && temp->type == COMMAND)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

char	**parse_cmd_args(t_token *node, int argc)
{
	t_token	*current;
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (argc + 1));
	i = 0;
	current = node;
	while (i < argc)
	{
		result[i++] = ft_strdup(current->literal);
		current = current->next;
	}
	return (result);
}

t_ast	*parse_cmd(t_token *node)
{
	t_ast	*cmd;
	int		argc;

	cmd = ast_new(COMMAND);
	argc = count_argc(node);
	
	if (cmd->literal == NULL)
		return (NULL);
	cmd->literal = parse_cmd_args(node, argc);
	return (cmd);
}

void	*parse_tokens(t_token *head)
{
	t_ast	*ast_head;
	t_token	*current;

	if (head == NULL)
	{
		printf("error, no tokens\n");
		return (NULL);
	}
	current = head;
	// leaving off here, next steps: add code for logical, pipes, and redir, in that order
	// https://www.chidiwilliams.com/posts/on-recursive-descent-and-pratt-parsing
	// use recursive descent, find the first logical node, then look for more. If you don't find one,
	// start looking for pipes, and so on, like this:
	// ast->left = parse_redir(), ast->right = parse_logical()
	// or perhaps the other way around
	// The last step is command, which I think is done
}
