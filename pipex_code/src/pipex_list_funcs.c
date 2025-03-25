/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_list_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 14:32:57 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-17 14:32:57 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_list	*pipex_lstnew(char *path, char **cmds)
{
	t_list	*new;

	if (cmds == NULL)
		return (NULL);
	new = malloc (sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->path = path;
	new->cmds = cmds;
	new->next = NULL;
	return (new);
}

void	pipex_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp -> next;
	tmp -> next = new;
}
