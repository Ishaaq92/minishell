/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:56:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/15 17:31:27 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_ast	*parse_logical(t_token **token, t_token **stop);
static t_ast	*parse_pipe(t_token **token, t_token **stop);
static t_ast	*parse_brackets(t_token **token, t_token **stop);

t_ast	*parse_tokens(t_token *head)
{
	t_ast	*ast_head;
	t_token	*start;
	t_token	*end;

	if (head == NULL)
	{
		printf("error, no tokens\n");
		return (NULL);
	}
	start = head;
	end = head;
	while (end->next != NULL)
		end = end->next;
	ast_head = parse_logical(&start, &end);
	return (ast_head);
}

// if you find a logical token, take these following steps:
// create an ast node
// start looking for pipes on the left hand side 
// look for more logical nodes on the right hand side
// return the logical node created to the function that called it
// if its the root node, it will be returned to the parse_tokens function
// if its a branch, it will connect to logical->right
// if you didn't find any logical nodes, start from the beginning and
// look for pipe nodes
static t_ast	*parse_logical(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*cut_off;
	t_token	*temp;
	t_ast	*logical;

	start = *token;
	temp = *token;
	while (temp != *stop)
		temp = temp->next;
	while (temp && (temp)->prev && (temp) != (start))
	{
		if (temp->type == RBRACE)
		{
			while (temp->type != LBRACE)
				temp = temp->prev;
		}
		if ((temp)->type == LOGICAL_AND || (temp)->type == LOGICAL_OR)
		{
			logical = ast_new(temp);
			logical->right = parse_pipe(&temp->next, stop);
			temp = temp->prev;
			logical->left = parse_logical(&start, &temp);
			return (logical);
		}
		temp = temp->prev;
	}
	return (parse_pipe(&start, stop));
}

static t_ast	*parse_pipe(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*temp;
	t_ast	*pipe;

	start = *token;
	while ((*token) && (*token)->next && (*token) != (*stop))
	{
		if ((*token)->type == PIPE)
		{
			pipe = ast_new(*token);
			temp = (*token)->next;
			pipe->left = parse_brackets(&start, token);
			pipe->right = parse_pipe(&temp, stop);
			return (pipe);
		}
		(*token) = (*token)->next;
	}
	return (parse_brackets(&start, stop));
}


// static t_ast	*parse_brackets(t_token **token, t_token **stop)
// {
// 	t_token	*start;
// 	t_token	*temp;
// 	t_token	*rbrace;
// 	t_ast	*logical;

// 	start = *token;
// 	temp = *token;

// 	while ((temp) && (temp)->next && (temp) != (*stop))
// 	{
// 		if (temp->type == LBRACE)
// 		{
// 			(temp) = (temp)->next;
// 			rbrace = temp;
// 			while (rbrace->next->type != RBRACE)
// 				rbrace = rbrace->next;
// 			while ((temp) && (temp)->next && (temp) != (*stop))
// 			{
// 				if ((temp)->type == LOGICAL_AND || (temp)->type == LOGICAL_OR)
// 				{
// 					logical = ast_new(temp);
// 					temp = (temp)->next;
// 					logical->left = parse_redir(&start, token);
// 					logical->right = parse_logical(&temp, &rbrace);
// 					return (logical);
// 				}
// 				(temp) = (temp)->next;
// 			}
// 		}
// 		(temp) = (temp)->next;
// 	}
// 	return (parse_redir(&start, stop));
// }

static t_ast	*parse_brackets(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*temp;
	t_token	*lbrace;
	t_token	*rbrace;
	t_ast	*logical;

	start = *token;
	temp = *token;

	while ((temp) && (temp)->next && (temp) != (*stop))
	{
		if (temp->type == LBRACE)
		{
			lbrace = temp;
			rbrace = temp;
			while (rbrace->next->type != RBRACE)
				rbrace = rbrace->next;
			temp = rbrace; // start at end
			while ((temp) && (temp)->prev && (temp) != (start))
			{
				if ((temp)->type == LOGICAL_AND || (temp)->type == LOGICAL_OR)
				{
					logical = ast_new(temp);
					logical->right = parse_pipe(&temp->next, &rbrace);
					temp = (temp)->prev;
					logical->left = parse_logical(&start->next, &temp);
					return (logical);
				}
				(temp) = (temp)->prev;
			}
		}
		(temp) = (temp)->next;
	}
	return (parse_redir(&start, stop));
}

void	free_ast(t_ast *ast)
{
	int	i;

	if (ast == NULL)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	i = 0;
	while(ast->literal && ast->literal[i])
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

// https://www.rioki.org/2016/04/18/recusive-descent-parser.html
// leaving off here, next steps: add code for logical, pipes, and redir
// https://www.chidiwilliams.com/posts/on-recursive-descent-and-pratt-parsing
// use recursive descent, find the first logical node, then look for more. 
// If you don't find one, start looking for pipes, and so on, like this:
// ast->left = parse_redir(), ast->right = parse_logical()
// or perhaps the other way around