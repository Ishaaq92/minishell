/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:48:46 by ishaaq            #+#    #+#             */
/*   Updated: 2025/04/17 22:56:28 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_lstsize(t_envp *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	env_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

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
	}
}

void	print_envp(t_envp **lst)
{
	t_envp	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		printf("%s\n", curr->literal);
		curr = curr->next;        
	}
}

// Purpose is to check variable exists. Returns malloc'd value of variable if exists. NULL otherwise. 
char	*value_envp(t_envp **lst, char *str)
{
	t_envp	*curr;
	int		length;

	length = ft_strlen(str);
	curr = *lst;
	while (curr != NULL)
	{
		if (ft_strncmp(str, curr->literal, length) == 0 && curr->literal[length] == '=')
			return (ft_strndup(&curr->literal[length + 1], ft_strlen(&curr->literal[length + 1])));
		curr = curr->next;
	}
	return (NULL);
}
