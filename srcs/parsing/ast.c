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

// https://www.chidiwilliams.com/posts/on-recursive-descent-and-pratt-parsing
// https://www.rioki.org/2016/04/18/recusive-descent-parser.html
static t_ast	*parse_logical(t_token **token, t_token **stop);
static t_ast	*parse_pipe(t_token **token, t_token **stop);
static t_ast	*parse_brackets(t_token **token, t_token **stop);

// ast generation starts here
// take the entire token list and pass start and end to parse_logical
// each of the parse_* functions loop through the token list and generate ast
// nodes if they find a valid token
// the search occurs in the following order:
// logical > pipe > brackets > redir > commands
t_ast	*parse_tokens(t_token *head)
{
	t_token	*start;
	t_token	*end;
	t_ast	*ast_head;

	if (head == NULL)
		return (NULL);
	start = head;
	end = ft_lstlast(head);
	ast_head = parse_logical(&start, &end);
	return (ast_head);
}

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

static t_ast	*parse_logical(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*temp;
	t_ast	*logical;

	start = *token;
	temp = *token;
	while (temp != *stop)
		temp = temp->next;
	while (temp && (temp)->prev && (temp) != (start))
	{
		if (temp->type == RBRACE)
			skip_braces(&temp);
		if ((temp)->type == LOGICAL_AND || (temp)->type == LOGICAL_OR)
		{
			logical = ast_new(temp);
			logical->right = parse_pipe(&temp->next, stop);
			logical->left = parse_logical(&start, &temp->prev);
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
			temp = rbrace;
			while ((temp) && (temp)->prev && (temp) != (start))
			{
				if ((temp)->type == LOGICAL_AND || (temp)->type == LOGICAL_OR)
				{
					logical = ast_new(temp);
					logical->right = parse_pipe(&temp->next, &rbrace);
					logical->left = parse_logical(&start->next, &temp->prev);
					return (logical);
				}
				(temp) = (temp)->prev;
			}
		}
		(temp) = (temp)->next;
	}
	return (parse_redir(&start, stop));
}
