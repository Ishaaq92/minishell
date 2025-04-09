/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:34:58 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/07 17:35:56 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



void	print_tokens(t_token **head)
{
	t_token *temp;

	temp = *head;
	printf("tokens: {");
	while (temp != NULL)
	{
		printf("%s[%i], ", temp->literal, temp->type);
		temp = temp->next;
	}
	printf("}\n");
}

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
