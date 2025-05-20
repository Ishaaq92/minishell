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

#include "../../inc/minishell.h"

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
	if (c == '<' || c == '>' || c == '|'
		|| c == '(' || c == ')' || c == '&')
		return (1);
	return (0);
}
