/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:54 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/15 20:00:14 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static ssize_t		find_equalsign(char *str);
static t_envp		*env_add(void);
static void			env_lstadd_back(t_envp **lst, t_envp *new);
int					ft_lstsize(t_envp *lst);

// ## functions needed
// DONE: a function to stitch the linked list into a double pointer array
// NEEDS TESTING: a function to remove elements from the linked list, then redo the array
// NEEDS TESTING: a function to free the linked list AND the double pointer array
// a function to update elements in the linked list, which would also update the double pointer array?
// a function that searches through the array and does param expansion

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
void	del_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
		free(envp[i++]);
}

void	remove_node(t_envp **lst,char **envp, char *var)
{
	t_envp	*curr;
	t_envp	*prev;

	curr = *lst;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_strcmp(var, curr->literal) == 0)
		{
			if (prev == NULL)
				*lst = curr->next;
			else
				prev->next = curr->next;
			free(curr->literal);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	del_envp(envp);
	stitch_env(*lst);
}

char	**stitch_env(t_envp *head)
{
	char	**envp;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(head);
	envp = (char **) malloc(sizeof(char *) * (size + 1));
	while (i < size && head->literal)
	{
		envp[i++] = head->literal;
		head = head->next;
	}
	envp[i] = '\0';
	return (envp);
}

t_envp	*set_envp(char **envp)
{
	size_t		i;
	int			sep;
	t_envp		*env_new;
	t_envp		*head;

	// this occurs when there are no environment variables which can happen
	// create a blank linked list or something if that occurs?
	if (!envp)
		return (NULL);
	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		env_new = env_add();
		env_new->literal = ft_strndup(envp[i], ft_strlen(envp[i]));
		env_lstadd_back(&head, env_new);
		i++;
	}
	return (head);
}

static ssize_t	find_equalsign(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i++])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

static t_envp	*env_add(void)
{
	t_envp		*env_new;

	env_new = (t_envp *) malloc(sizeof(t_envp));
	env_new->literal = NULL;
	env_new->next = NULL;
	return (env_new);
}

static void	env_lstadd_back(t_envp **lst, t_envp *new)
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
