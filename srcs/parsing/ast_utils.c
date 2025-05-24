/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:21:46 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 16:21:46 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// malloc and initialises an ast node
t_ast	*ast_new(t_token *token)
{
	t_ast	*new;

	if (token == NULL)
		return (NULL);
	new = (t_ast *)malloc(sizeof(t_ast));
	new->left = NULL;
	new->right = NULL;
	new->literal = NULL;
	new->token = token;
	new->type = token->type;
	return (new);
}

void	free_ast(t_ast *ast)
{
	int	i;

	if (ast == NULL)
		return ;
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	i = 0;
	while (ast->literal && ast->literal[i])
		i++;
	free(ast->literal);
	free(ast);
}

void	print_ast(t_ast *ast, int i)
{
	int	j;

	j = 0;
	if (ast == NULL || ast->token->literal == NULL)
		return ;
	while (j++ < i)
		printf("	");
	printf("%s\n", ast->token->literal);
	print_ast(ast->left, --i);
	print_ast(ast->right, i + 2);
}

// this helper function skips over brackets while parsing logical ops
// the logical operators inside brackets have lower priority and will
// be handled later by parse_brackets
void	skip_braces(t_token **temp)
{
	int		count;

	count = 0;
	while ((*temp) && (*temp)->prev)
	{
		if ((*temp)->type == RBRACE)
			count++;
		if ((*temp)->type == LBRACE)
		{
			count--;
			if (count <= 0)
				break ;
		}
		(*temp) = (*temp)->prev;
	}
}

// used by parse_brackets to find the right brace of a given lbrace
t_token	*get_rbrace(t_token *lbrace)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = lbrace;
	while ((temp) && (temp)->next)
	{
		if ((temp)->type == LBRACE)
			count++;
		if ((temp)->type == RBRACE)
		{
			count--;
			if (count <= 0)
				return (temp);
		}
		(temp) = (temp)->next;
	}
	return (temp);
}
