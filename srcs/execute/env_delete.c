/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:41:03 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/14 15:45:05 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Note that deleting the lst will delete the envp array.
void	del_lst(t_envp **lst)
{
	t_envp	*tmp;
	t_envp	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->literal)
			free(curr->literal);
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

// Note that deleting the envp will delete the linked list literals.
void	del_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
}

// Works but need to check effects on the array.
void	remove_node(t_data *data, char *var)
{
	t_envp	*curr;
	t_envp	*prev;
	int		len;

	curr = data->env_llst;
	prev = NULL;
	len = ft_strlen(var);
	while (curr != NULL)
	{
		if (curr->literal && !ft_strncmp(var, curr->literal, len)
			&& (curr->literal[len] == '=' || curr->literal[len] == '\0'))
		{
			if (prev == NULL)
				data->env_llst = curr->next;
			else
				prev->next = curr->next;
			(free(curr->literal), free(curr));
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
