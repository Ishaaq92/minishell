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

#include "../../inc/minishell.h"

// treat whatever is left after all operators are parsed as a command plus
// arguments
t_ast	*parse_cmd(t_token	**token)
{
	t_ast	*cmd;

	if (token == NULL || (*token) == NULL)
		return (NULL);
	while (*token && ((*token)->type == LBRACE || (*token)->type == RBRACE))
		(*token) = (*token)->next;
	cmd = ast_new(*token);
	if (cmd)
		cmd->literal = parse_cmd_args(*token, count_argc(*token));
	if (cmd && cmd->literal == NULL)
		return (free(cmd), NULL);
	return (cmd);
}

// TODO: this is useful in other places too
int	is_token_redir(t_type type)
{
	if (type < 6 && type > 1)
		return (1);
	return (0);
}

// this helper function generates a double pointer array of strings which
// are the command name followed by its arguments
char	**parse_cmd_args(t_token *token, int argc)
{
	t_token	*current;
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (argc + 1));
	if (!result)
		return (NULL);
	i = 0;
	current = token;
	if (current && current->literal && current->literal[0] == '\0')
		current = current->next;
	while (i < argc)
	{
		if (current && is_token_redir(current->type))
			if (current->next)
				current = current->next->next;
		result[i++] = current->literal;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

// this helper function counts the arguments the command will have
// based on how many tokens have the type WORD in a row
int	count_argc(t_token *token)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = token;
	if (temp->literal[0] == '\0')
		temp = temp->next;
	while (temp)
	{
		if (temp && is_token_redir(temp->type))
		{
			if (temp->next)
				temp = temp->next->next;
		}
		else if (temp->type != WORD)
			break ;
		else
		{
			count++;
			temp = temp->next;
		}
	}
	return (count);
}
