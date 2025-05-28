/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:54 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/27 15:55:02 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_envp		*env_add(void);
int					ft_lstsize(t_envp *lst);

// MUST INCLUDE FULL STRING: eg. 'PWD=/Users/tim'
int	add_node(t_data *data, char *string)
{
	t_envp	*new;
	char	*plus;

	plus = ft_strchr(string, '+');
	if (plus && *(plus + 1) == '=')
		ft_memmove(plus, plus + 1, ft_strlen(plus));
	new = env_add();
	new->literal = ft_strdup(string);
	env_lstadd_back(&data->env_llst, new);
	return (0);
}

t_envp	*set_envp(char **envp)
{
	size_t		i;
	t_envp		*env_new;
	t_envp		*head;

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

void	*env_alter(t_data *data, char *key, char *value)
{
	t_envp		*curr;
	char		*temp;
	int			len;

	len = ft_strlen(key);
	curr = data->env_llst;
	while (curr != NULL && ft_strncmp(curr->literal, key, len) != 0)
		curr = curr->next;
	if (curr == NULL)
	{
		temp = ft_strjoin(key, value);
		return (add_node(data, temp), free(temp), NULL);
	}
	free(curr->literal);
	curr ->literal = ft_strjoin(key, value);
	return (NULL);
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
	if (!envp)
		return (NULL);
	while (i < size && head->literal)
	{
		envp[i] = ft_strdup(head->literal);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}
