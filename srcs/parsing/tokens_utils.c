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

int	open_lbrace(t_token *token)
{
	t_token	*temp;
	int		count;

	temp = token;
	count = 1;
	while (temp)
	{
		if (temp->type == LBRACE)
			count++;
		if (temp->type < 2 || temp->next == NULL)
			count--;
		if (temp->type == RBRACE && (temp->next && temp->next->type < 7))
			count--;
		if (temp->type == RBRACE || count == 0)
			break ;
		temp = temp->next;
	}
	if (count)
		return (1);
	return (0);
}

int	check_brackets(t_token **head)
{
	t_token	*temp;
	int		open_brackets;

	temp = *head;
	open_brackets = 0;
	while (temp)
	{
		if (temp->type == LBRACE)
		{
			open_brackets++;
			if (temp->next->type == RBRACE || open_lbrace(temp->next))
				return (1);
		}
		else if (temp->type == RBRACE)
			open_brackets--;
		temp = temp->next;
	}
	if (open_brackets)
		return (1);
	return (0);
}

// checks validity of the token list, if the starting token is
// a wrong operator or if the token list ends in an operator
int	check_valid_order(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp->type < 2 || tmp->type == PIPE || check_brackets(head))
		return (1);
	while (tmp)
	{
		if (tmp->open_quote)
			return (ft_perror(), 1);
		if (tmp->type > 1 && tmp->type < 6)
			if (tmp->next && tmp->next->type != WORD)
				return (1);
		// commented out because "echo <123 <456" 
		// if (tmp->next && tmp->type < 7 && tmp->next->type < 7)
		// 	return (1);
		if (tmp->next == NULL && tmp->type < 7)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
