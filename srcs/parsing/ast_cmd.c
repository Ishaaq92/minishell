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

static char		**parse_cmd_args(t_token *node, int argc);
static int		count_argc(t_token *node);

// treat whatever is left after all operators are parsed as a command plus
// arguments
t_ast	*parse_cmd(t_token	**node)
{
	t_ast	*cmd;

	if (node == NULL || (*node) == NULL)
		return (NULL);
	while ((*node)->type == LBRACE || (*node)->type == RBRACE)
		(*node) = (*node)->next;
	cmd = ast_new(*node);
	cmd->literal = parse_cmd_args(*node, count_argc(*node));
	if (cmd->literal == NULL)
		return (free(cmd), NULL);
	return (cmd);
}

// this helper function generates a double pointer array of strings which
// are the command name followed by its arguments
static char	**parse_cmd_args(t_token *node, int argc)
{
	t_token	*current;
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (argc + 1));
	if (!result)
		return (NULL);
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

// this helper function counts the arguments the command will have
// based on how many tokens have the type WORD in a row
static int	count_argc(t_token *node)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = node;
	while (temp && temp->type == WORD)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
