/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:41:03 by ishaaq            #+#    #+#             */
/*   Updated: 2025/04/27 14:26:54 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Note that deleting the lst will delete the envp array.
void	del_lst(t_envp **lst)
{
	t_envp	*tmp;
	t_envp	*curr;

	curr = *lst;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr->literal);
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

// Note that deleting the envp will delete the linked list literals.
// CHECK FOR LEAKS
void	del_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
		free(envp[i++]);
	free(envp);
}

// Works but need to check effects on the array.
void	remove_node(t_envp **lst, char ***envp, char *var)
{
	t_envp	*curr;
	t_envp	*prev;

	curr = *lst;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_strncmp(var, curr->literal, ft_strlen(var)) == 0)
		{
			if (prev == NULL)
				*lst = curr->next;
			else
				prev->next = curr->next;
			free(curr->literal);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	del_array(*envp);
	*envp = stitch_env(*lst);
}
