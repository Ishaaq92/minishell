/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 14:34:40 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 14:34:40 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// simple function that matches the operator with the correct enum
enum e_type	set_op_type(char *str)
{
	while (*str >= '0' && *str <= '9')
		str++;
	if (!ft_strncmp("<<", str, 2))
		return (IN_HEREDOC);
	else if (!ft_strncmp(">>", str, 2))
		return (OUT_APPEND);
	else if (!ft_strncmp("<", str, 1))
		return (REDIR_IN);
	else if (!ft_strncmp(">", str, 1))
		return (REDIR_OUT);
	else if (!ft_strncmp("||", str, 2))
		return (LOGICAL_OR);
	else if (!ft_strncmp("&&", str, 2))
		return (LOGICAL_AND);
	else if (!ft_strncmp("|", str, 1))
		return (PIPE);
	else if (!ft_strncmp("(", str, 1))
		return (LBRACE);
	else if (!ft_strncmp(")", str, 1))
		return (RBRACE);
	else
		return (ERROR);
}

// returns true if character is a blank space
int	is_blank(char c)
{
	if (c == ' ' || (c <= '\r' && c >= '\t'))
		return (1);
	return (0);
}

// returns true if the character is an operator
int	is_op(char c)
{
	if (c == '<' || c == '>' || \
		c == '|' || \
		c == '(' || c == ')' || \
		c == '&')
		return (1);
	return (0);
}

// checks validity of the token list, if the starting token is
// a wrong operator or if the token list ends in an operator
int	check_valid_order(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp->type == LOGICAL_AND || tmp->type == LOGICAL_OR \
		|| tmp->type == PIPE)
		return (1);
	while (tmp)
	{
		if (tmp->open_quote)
			return (ft_perror(), 1);
		// commented out because "echo <123 <456" 
		// if (tmp->next && tmp->type < 7 && tmp->next->type < 7)
		// 	return (1);
		if (tmp->next == NULL && tmp->type < 7)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
