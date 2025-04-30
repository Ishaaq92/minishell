/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:24:24 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/17 19:25:44 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		count_argc(t_token *node);
static char		**parse_cmd_args(t_token *node, int argc);

t_ast	*ast_new(t_token *token)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->left = NULL;
	new->right = NULL;
	new->literal = NULL;
	new->parent = NULL;
	new->token = token;
	new->type = token->type;
	return (new);
}

t_ast	*parse_cmd(t_token	**node)
{
	t_ast	*cmd;
	int		argc;

	if (node == NULL || *node == NULL)
		return (NULL);
	while ((*node)->type == LBRACE || (*node)->type == RBRACE)
		(*node) = (*node)->next;
	cmd = ast_new(*node);
	argc = count_argc(*node);
	cmd->literal = parse_cmd_args(*node, argc);
	if (cmd->literal == NULL)
		return (NULL);
	return (cmd);
}

static int	count_argc(t_token *node)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = node;
	while (temp && temp->type == COMMAND)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

static char	**parse_cmd_args(t_token *node, int argc)
{
	t_token	*current;
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (argc + 1));
	i = 0;
	current = node;
	while (i < argc)
	{
		result[i++] = ft_strdup(current->literal);
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}
