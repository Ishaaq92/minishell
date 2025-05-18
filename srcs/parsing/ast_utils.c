/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:31:02 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/13 18:53:27 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// malloc and initialises an ast node
t_ast	*ast_new(t_token *token)
{
	t_ast	*new;

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
	{
		// free(ast->literal[i]);
		i++;
	}
	// free(ast->literal);
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
