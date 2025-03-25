/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-05 11:55:03 by avalsang          #+#    #+#             */
/*   Updated: 2024-12-05 11:55:03 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new -> next = *lst;
		*lst = new;
	}
}
/* 
int main()
{
	t_list * l =  ft_lstnew((void*)42);
	l->content = (void*)42;
	ft_lstadd_front(&l, ft_lstnew((void*)1));

	printf("content = %i\n", l->content == (void*)1);
	printf("next = %i\n", l->next->content == (void *)42);
}
 */