/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:40:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/07 17:23:45 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_lstnew(char *str)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->literal = str;
	token->next = NULL;
	token->type = 0;
	token->open_quote = 0;
	return (token);
}

// for now, pretend abstract syntax tree is an abstract syntax line
// later, create logic that adds new tokens as children
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

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

void	print_tokens(t_token **head)
{
	t_token *temp;

	temp = *head;
	printf("tokens: {");
	while (temp != NULL)
	{
		printf("%s[%i], ", temp->literal, temp->type);
		temp = temp->next;
	}
	printf("}\n");
}

int	is_blank(char c)
{
	if (c == ' ' || (c <= '\r' && c >= '\t'))
		return (1);
	return (0);
}

int	is_op(char c)
{
	if (c == '<' || c == '>' || \
		c == '|' || \
		c == '(' || c == ')' || \
		c == '&')
		return (1);
	return (0);
}

int	handle_quotes(char *str, int *i, t_token *token)
{
	char	quote_char;
	char	*temp;
	int		open_quotes;

	quote_char = str[*i];
	open_quotes = 1;
	if (quote_char == '\'' || quote_char == '\"')
	{
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == quote_char)
			{
				(*i)++;
				open_quotes = 0;
				break ;
			}
			(*i)++;
		}
	}
	else if (quote_char == '\\')
		(*i) += 2;
	if (open_quotes)
		return (1);
	return (0);
}

int	compare_op(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}


enum e_type		set_op_type(char *str)
{
	// if (strcmp("<", token->literal))
	// {
	// 	token->type = REDIRECT_IN;
	// }
	// else if (strcmp(">", token->literal))
	// {
	// 	token->type = REDIRECT_OUT;
	// }
	while (*str >= '0' && *str <= '9')
		str++;	
	if (!ft_strncmp("<<", str, 2))
		return (REDIRECT_HEREDOC);
	else if (!ft_strncmp(">>", str, 2))
		return (REDIRECT_APPEND);
	else if (!ft_strncmp("<", str, 1))
		return (REDIRECT_IN);
	else if (!ft_strncmp(">", str, 1))
		return (REDIRECT_OUT);
	else if (!ft_strncmp("||", str, 2))
		return (LOGICAL_OR);
	else if (!ft_strncmp("&&", str, 2))
		return (LOGICAL_AND);
	else if (!ft_strncmp("|", str, 1))
		return (PIPE);
	else
		return (ERROR);
}

void	handle_op(char **str, char **literal, t_token *token)
{
	int		i;

	i = 0;
	while (ft_strchr("<>&|()", (*str)[i]))
	{
		i++;
		if ((*str)[i] == (*str)[i - 1])
			continue ;
		else 
			break ;
	}
	*literal = ft_strndup(*str, i);
	token->type = set_op_type(*literal);
	(*str) += i;
}

void	handle_word(char **str, char **literal, t_token *token)
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
	token->type = COMMAND;
	(*str) += i;
}

void	handle_num(char **str, char **literal, t_token *token)
{
	int		i;

	i = 0;
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
	{
		i++;
	}
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

int	check_valid_order(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp->type == LOGICAL_AND || tmp->type == LOGICAL_OR || tmp->type == PIPE)
		return (1);
	while (tmp)
	{
		if (tmp->next && tmp->type < 7 && tmp->next->type < 7)
			return (1);
		if (tmp->next == NULL && tmp->type < 7)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


int	create_tokens(char *str, t_token **head)
{
	t_token *token;

	while (*str)
	{
		while (is_blank(*str))
			str++;
		token = ft_lstnew(NULL);
		if (*str >= '0' && *str <= '9')
			handle_num(&str, &token->literal, token);
		else if (*str && is_op(*str))
			handle_op(&str, &token->literal, token);
		else if (*str)
			handle_word(&str, &token->literal, token);
		if (!token->literal)
			free(token);
		else
			ft_lstadd_back(head, token);
	}
	if (check_valid_order(head) == 1)
		printf("Invalid order of tokens\n");
	print_tokens(head);
}

// // a token that doesn't contain meta characters and isn't quoted is a word
// // a token with no quotes and at least one meta character is an operator
// int	create_tokens(char *str, t_token **head)
// {
// 	char	*buffer;
// 	char	*token_start;
// 	int		i;
// 	int		j;
// 	i = 0;
// 	while (str && str[i])// process the entire line? Or do we break upon newline
// 	{
// 		j = 0;
// 		while (str[i + j] && !is_blank(str[i + j]))
// 		{
// 			if (ft_strchr("\'\"", str[i + j]))
// 			{
// 				; // handle quotes, do not break the token
// 			}
// 			else if (is_op(str[i + j])) // operators break tokens
// 				break ;
// 			else if (str[i + j] == '\\')
// 			{
// 				j++;
// 				// what if char after backslash is empty? Need to prompt a PS2
// 			}
// 			j ++;
// 		}
// 		if (j)
// 			ft_lstadd_back(head, ft_lstnew(ft_substr(str, i, j)));
// 		i = i + j + 1;
// 	}
// 	print_tokens(head);
// 	return (0);
// }
