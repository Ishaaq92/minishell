/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:54 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/28 10:35:21 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_envp		*env_add(void);
int					ft_lstsize(t_envp *lst);

// ## functions needed
// DONE: a function to stitch the linked list into a double pointer array
//		stitch_env()
// DONE: a function to remove elements from the linked list, then redo the array
//		remove_node() 
// DONE: a function that returns the value of env variable
//		value_envp() 
// DONE: a function to update elements in the array, which would also update the array?
//		append_node()
// a function that searches through the array and does param expansion
//		Not sure. value_envp() does something similar.
// CHECK FOR LEAKS: a function to free the linked list AND the double pointer array

// MUST INCLUDE FULL STRING: eg. 'PWD=/Users/tim'
void	append_node(t_envp **lst, char **array, char *string)
{
	t_envp	*new;	
	
	new = env_add();
	new ->literal = string;
	env_lstadd_back(lst, new);
	del_array(array);
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
// This function does NOT free key or value. Only free curr->literal.
// KEY MUST INCLUE THE '=' CHARACTER. Eg. 'PWD='
void	env_alter(t_data *data, char *key, char *value)
{
	t_envp		*curr;
	int			len;

	len = ft_strlen(key);
	curr = data->env_llst;
	while (curr != NULL && ft_strncmp(curr->literal, key, len) != 0)
		curr = curr->next;
	if (curr == NULL)
		return ;
	free(curr->literal);
	curr ->literal = ft_strjoin(key, value);
	// Do we need to restitch the char **envp array?
}

static t_envp	*env_add(void)
{
	t_envp		*env_new;

	env_new = (t_envp *) malloc(sizeof(t_envp));
	env_new->literal = NULL;
	env_new->next = NULL;
	return (env_new);
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
	envp[i] = NULL;
	return (envp);
}
