/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:40:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/25 16:52:45 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_quotes(char *str, int *i, t_token *token);
static void	handle_op(char **str, char **literal, t_token *token);
static void	handle_word(char **str, char **literal, t_token *token);
static void	handle_num(char **str, char **literal, t_token *token);

// takes input as a string and loops through every character
// if a character is an operator token or start of a word, begin tokenising it
// at the end, check if a token was created, add it to linked list if it was
// TODO: the while loop doesn't have str++ at the end... why did we design it like that? Is there any character that can cause it to end up in an infinite loop?
int	create_tokens(char *str, t_token **head)
{
	t_token		*token;

	while (*str)
	{
		while (is_blank(*str))
			str++;
		token = ft_lstnew(NULL);
		if (ft_isdigit(*str))
			handle_num(&str, &token->literal, token);
		else if (is_op(*str))
			handle_op(&str, &token->literal, token);
		else if (*str != '\0')
			handle_word(&str, &token->literal, token);
		if (!token->literal)
			free(token);
		else
			ft_lstadd_back(head, token);
	}
	if (*head && check_valid_order(head))
		return (printf("Invalid order of tokens\n"), 1);
	return (0);
}

// a number can be part of a word or a redir operator
// loop through the number, if its immediately followed by a redir token,
// tokenise it as an operator
// otherwise handle it as a 'word'
static void	handle_num(char **str, char **literal, t_token *token)
{
	int		i;

	i = 0;
	while (ft_isdigit((*str)[i]))
		i++;
	if ((*str)[i] && ((*str)[i] != ' ') && ft_strchr("<>", (*str)[i]))
	{
		i++;
		if ((*str)[i] && (*str)[i] == (*str)[i - 1])
			i++;
		*literal = ft_strndup(*str, i);
		token->type = set_op_type(*literal);
		(*str) += i;
		return ;
	}
	handle_word(str, literal, token);
}

// if the current character is an operator token, begin the token
// keep adding characters to the same token until the token is no longer valid
// tokenising ends when the character is no longer the same operator or is a space
static void	handle_op(char **str, char **literal, t_token *token)
{
	int		i;

	i = 0;
	if (ft_strchr("<>&|", (*str)[i]))
	{
		i++;
		if ((*str)[i] == (*str)[i - 1])
			i++;
	}
	else if ((*str)[i] == '(' || (*str)[i] == ')')
		i++;
	*literal = ft_strndup(*str, i);
	token->type = set_op_type(*literal);
	(*str) += i;
}

// if a character is not a number or an operator or a space, it has to be a word
// loop through the string until you find a breakpoint, a token or a space
static void	handle_word(char **str, char **literal, t_token *token)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if (ft_strchr("\'\"\\", (*str)[i]))
			handle_quotes(*str, &i, token);
		else if (is_blank((*str)[i]) || is_op((*str)[i]))
			break ;
		i++;
	}
	*literal = ft_strndup(*str, i);
	token->type = WORD;
	(*str) += i;
}

// if you encounter a quote, the spaces and operators inside it do not break the token
// store the quote character, and keep looping through until you find it again
// in bash, multiple quotes are treated from left to right, not as nested group
static int	handle_quotes(char *str, int *i, t_token *token)
{
	char	quote_char;
	char	*temp;

	quote_char = str[*i];
	token->open_quote = 1;
	if (quote_char == '\'' || quote_char == '\"')
	{
		(*i)++;
		while (str[*i])
		{
			if (str[(*i)] == quote_char)
			{
				token->open_quote = 0;
				break ;
			}
			(*i)++;
		}
	}
	else if (quote_char == '\\')
		(*i) += 2;
	if (token->open_quote)
		return (1);
	return (0);
}
