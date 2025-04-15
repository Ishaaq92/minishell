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

#include "../inc/minishell.h"

static t_ast	*parse_redir2(t_token **token, t_token **stop);
static t_ast	*parse_file(t_token **token);

t_ast	*parse_redir(t_token **token, t_token **stop)
{
	t_token	*start;
	t_token	*next_token;
	t_ast	*redir;

	if (!*token)
		return (NULL);
	start = *token;
	if ((*token)->type > 1 && (*token)->type < 6)
		return (parse_redir2(token, stop));
	while ((*token) && (*token)->next && (*token) != (*stop))
	{
		next_token = (*token)->next;
		if ((*token)->next->type > 1 && (*token)->next->type < 6)
		{
			redir = ast_new((*token)->next);
			(*token)->next = (next_token)->next->next;
			redir->left = parse_redir(&start, stop);
			redir->right = parse_file(&next_token->next);
			(*token)->next = next_token;
			return (redir);
		}
		*token = next_token;
	}
	return (parse_cmd(&start));
}

static t_ast	*parse_redir2(t_token **token, t_token **stop)
{
	t_ast	*redir;
	t_token	*start;
	t_token	*temp;

	start = *token;
	redir = ast_new(*token);
	temp = *token;
	(*token) = (*token)->next->next;
	redir->left = parse_redir(token, stop);
	redir->right = parse_file(&start->next);
	*token = temp;
	return (redir);
}

static t_ast	*parse_file(t_token **token)
{
	t_ast	*path;

	path = ast_new(*token);
	path->type = PATH;
	return (path);
}
