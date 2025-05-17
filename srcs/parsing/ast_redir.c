/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:23:07 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/15 17:07:21 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ast	*create_redir_node(t_token *start, t_token **stop, t_token *temp, t_token *next_token);
static t_ast	*parse_redir2(t_token **token, t_token **stop);
static t_ast	*parse_file(t_token **token);

// look for redir tokens from the beginning, create and return a node if you
// find one
// if no redir tokens are found, parse the given list as a command from start
// TODO: find better names for the two helper functions, and norm the file
t_ast	*parse_redir(t_token **token, t_token **stop)
{
	t_token		*start;
	t_token		*temp;
	t_token		*next_token;

	if (*token == NULL)
		return (NULL);
	if ((*token)->type > 1 && (*token)->type < 6)
		return (parse_redir2(token, stop));
	start = *token;
	temp = *token;
	while (temp && temp->next && temp != (*stop))
	{
		next_token = temp->next;
		if (temp->next->type > 1 && temp->next->type < 6)
			return (create_redir_node(start, stop, temp, next_token));
		temp = next_token;
	}
	return (parse_cmd(&start));
}

// this helper function handles the scenario where a redir token has
// a command attached to it or is in the middle of a token list
static t_ast	*create_redir_node(t_token *start, t_token **stop, t_token *temp, t_token *next_token)
{
	t_ast		*redir;

	redir = ast_new(next_token);
	temp->next = (next_token)->next->next;
	redir->left = parse_redir(&start, stop);
	redir->right = parse_file(&next_token->next);
	temp->next = next_token;
	return (redir);
}

// this helper function deals with cases where the redir token is at
// the start of the list
static t_ast	*parse_redir2(t_token **token, t_token **stop)
{
	t_ast		*redir;
	t_token		*start;
	t_token		*temp;

	start = *token;
	redir = ast_new(*token);
	temp = *token;
	(*token) = (*token)->next->next;
	redir->left = parse_redir(token, stop);
	redir->right = parse_file(&start->next);
	*token = temp;
	return (redir);
}

// this helper function stores the filename as an ast node
static t_ast	*parse_file(t_token **token)
{
	t_ast		*path;

	path = ast_new(*token);
	path->type = PATH;
	return (path);
}
