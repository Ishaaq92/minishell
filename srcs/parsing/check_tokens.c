/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:05:21 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:05:21 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_brackets(t_token *token);
// static int	check_brackets(t_token **head);
// static int	open_lbrace(t_token *token);

// checks validity of the token list, if the starting token is
// a wrong operator or if the token list ends in an operator
int	check_valid_order(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp->type < 2 || tmp->type == PIPE || check_brackets(tmp))
		return (1);
	while (tmp)
	{
		if (tmp->open_quote)
			return (1);
		if (tmp->type > 1 && tmp->type < 6)
			if (tmp->next && tmp->next->type != WORD)
				return (1);
		if (tmp->next == NULL && tmp->type < 7)
			return (1);
		tmp = tmp->next;
	}
	tmp = ft_lstlast(*head);
	if (tmp->type < 7 || tmp->type == LBRACE)
		return (1);
	return (0);
}

// check brackets
// L and r brackets must never be next to each other
// each brace must have an operator on either side, or a null token
// must have an even number of l and r brackets

static int	check_brackets(t_token *token)
{
	int		total;

	total = 0;
	while (token)
	{
		if (token->type == LBRACE)
		{
			total++;
			if (token->next && token->next->type == RBRACE)
				return (1);
		}
		else if (token->type == RBRACE)
		{
			total++;
			if (token->next && (token->next->type == LBRACE || token->next->type == WORD))
				return (1);
		}
		token = token->next;
	}
	return (total % 2);
}


// static int	check_brackets(t_token **head)
// {
// 	t_token	*temp;
// 	int		open_brackets;

// 	temp = *head;
// 	open_brackets = 0;
// 	while (temp)
// 	{
// 		if (temp->type == LBRACE)
// 		{
// 			open_brackets++;
// 			if ((temp->next && temp->next->type == RBRACE) || open_lbrace(temp->next))
// 				return (1);
// 		}
// 		else if (temp->type == RBRACE)
// 			open_brackets--;
// 		temp = temp->next;
// 	}
// 	if (open_brackets)
// 		return (1);
// 	return (0);
// }

// static int	open_lbrace(t_token *token)
// {
// 	t_token	*temp;
// 	int		count;

// 	temp = token;
// 	count = 1;
// 	while (temp)
// 	{
// 		if (temp->type == LBRACE)
// 			count++;
// 		if (temp->type < 2 || temp->next == NULL)
// 			count--;
// 		if (temp->type == RBRACE && (temp->next && temp->next->type < 7))
// 			count--;
// 		if (temp->type == RBRACE && count == 0)
// 			break ;
// 		temp = temp->next;
// 	}
// 	if (count)
// 		return (1);
// 	return (0);
// }
