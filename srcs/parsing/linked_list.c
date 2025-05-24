/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:21:46 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 16:21:46 by avalsang         ###   ########.fr       */
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
	token->fd = -1;
	token->type = 0;
	token->open_quote = 0;
	token->next = NULL;
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
			if ((*lst)->fd != -1)
				close((*lst)->fd);
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
