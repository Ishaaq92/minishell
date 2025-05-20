/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:32:21 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:32:21 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	connect_token_list(t_data *data, t_token *current, t_token *list);
static void	rebuild_token_list(t_data *data, t_ast *node, t_token **current);
void	reset_node_literal(t_ast *node);

void	clean_args(t_data *data, t_ast *node)
{
	t_token	*current;

	current = node->token;
	while (current && current->type == WORD)
	{
		if (current->literal)
		{
			if (ft_strchr(current->literal, '$'))
				rebuild_token_list(data, node, &current);
			remove_quotes(current->literal);
		}
		current = current->next;
	}
	reset_node_literal(node);
}

static void	rebuild_token_list(t_data *data, t_ast *node, t_token **current)
{
	t_token		*list;

	list = NULL;
	param_sub(data, &(*current)->literal);
	create_tokens((*current)->literal, &list);
	if (list)
	{
		connect_token_list(data, (*current), list);
		if ((*current) == node->token)
			node->token = list;
		ft_lstdelone((*current));
		(*current) = list;
	}
}

void	reset_node_literal(t_ast *node)
{
	free(node->literal);
	node->literal = parse_cmd_args(node->token, count_argc(node->token));
}

// this function will handle the newly created linked list of tokens from 
// param_sub
// first it will set all tokens inside it to WORD, so tokens like ">" or "|" are
// handled as words, not operators, like bash
// then, if list->next exists, meaning the token was split into chunks and isn't
// just one single token after substitution, attach the list
static void	connect_token_list(t_data *data, t_token *current, t_token *list)
{
	t_token		*temp;
	t_token		*list_last;

	temp = list;
	while (temp)
	{
		temp->type = WORD;
		temp = temp->next;
	}
	temp = current->prev;
	if (temp)
		temp->next = list;
	else
		data->token_list = list;
	list->prev = temp;
	list_last = ft_lstlast(list);
	list_last->next = current->next;
	temp = current->next;
	if (temp)
		temp->prev = list_last;
}
