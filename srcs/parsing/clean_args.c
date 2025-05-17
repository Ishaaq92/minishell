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

static void	update_tokens(t_data *data, t_token *current, t_token *list);

void	clean_args(t_data *data)
{
	t_token	*current;
	t_token	*list;

	current = data->token_list;
	list = NULL;
	while (current)
	{
		if (current->type == WORD)
			if (current->literal)
			{
				if (ft_strchr(current->literal, '$'))
				{
					param_sub(data, &current->literal);
					create_tokens(current->literal, &list);
					update_tokens(data, current, list);
					ft_lstdelone(current);
					current = list;
				}
				remove_quotes(current->literal);
			}
		current = current->next;
		list = NULL;
	}
}

static void	update_tokens(t_data *data, t_token *current, t_token *list)
{
	t_token		*temp;
	t_token		*list_last;

	temp = list;
	while (temp)
	{
		temp->type = WORD;
		temp = temp->next;
	}
	if (list->next)
	{
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
}
