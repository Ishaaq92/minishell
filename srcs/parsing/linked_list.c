/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:34:58 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/17 20:54:20 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_lstnew(char *str)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->literal = str;
	token->next = NULL;
	token->type = 0;
	token->open_quote = 0;
	token->prev = NULL;
	return (token);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp -> next != NULL)
			tmp = tmp -> next;
		tmp -> next = new;
		new -> prev = tmp;
	}
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free((*lst)->literal);
			free((*lst));
			(*lst) = tmp;
		}
	}
}

void	ft_lstdelone(t_token *args)
{
	if (args->literal)
		free(args->literal);
	free(args);
}
