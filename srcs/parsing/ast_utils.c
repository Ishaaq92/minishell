/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 14:31:02 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 14:31:02 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_ast(t_ast *ast)
{
	int	i;

	if (ast == NULL)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	i = 0;
	while (ast->literal && ast->literal[i])
	{
		free(ast->literal[i]);
		i ++;
	}
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
