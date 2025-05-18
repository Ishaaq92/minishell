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

#include "../../inc/minishell.h"

// https://www.chidiwilliams.com/posts/on-recursive-descent-and-pratt-parsing
// https://www.rioki.org/2016/04/18/recusive-descent-parser.html

static t_ast	*parse_logical(t_token **token, t_token **stop);
static t_ast	*parse_pipe(t_token **token, t_token **stop);
static t_ast	*parse_brackets(t_token **token, t_token **stop);
static void		skip_braces(t_token **temp);

// ast generation starts here
// take the entire token list and pass start and end to parse_logical
// each of the parse_* functions loop through the token list and generate ast
// nodes if they find a valid token
// the search occurs in the following order:
// logical > pipe > brackets > redir > commands
// TODO: can you get rid of the end variable by passing the function directly?
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

// parses token list in reverse order looking for logical nodes
// reverse order is used to make sure execution behaves like bash
// if you parse left to right, the logical operators on the left have
// greater priority on the tree, which can cause the shell to abort early
// in bash, logical operators only care about the preceding command
// eg: echo c1 || echo c2 && echo c3 should print c1 AND c3
// parsing left to right causes the shell to behave like this:
// echo c1 || (echo c2 && echo c3)
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
		if (temp == start)
			continue ;
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

// this helper function skips over brackets while parsing logical ops
// the logical operators inside brackets have lower priority and will
// be handled later by parse_brackets
static void	skip_braces(t_token **temp)
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

// once logical operators are sorted, look for pipes
// this search is done left to right, which does not hinder the reverse
// logical search 
static t_ast	*parse_pipe(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*temp;
	t_ast	*pipe;

	start = *token;
	temp = *token;
	while (temp && temp->next && temp != (*stop))
	{
		if (temp->type == PIPE)
		{
			pipe = ast_new(temp);
			temp = temp->next;
			pipe->left = parse_brackets(&start, &temp);
			pipe->right = parse_pipe(&temp, stop);
			return (pipe);
		}
		temp = temp->next;
	}
	return (parse_brackets(&start, stop));
}

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

// after pipes, begin looking for brackets
// if a bracket is found, the inside content is sent to parse_logical
// and treated the same way as logical operators outside brackets
static t_ast	*parse_brackets(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*temp;
	t_token	*rbrace;

	start = *token;
	temp = *token;
	while ((temp) && (temp)->next && (temp) != (*stop))
	{
		if (temp->type == LBRACE)
		{
			rbrace = get_rbrace(temp);
			return (parse_logical(&temp->next, &rbrace->prev));
		}
		(temp) = (temp)->next;
	}
	return (parse_redir(&start, stop));
}
