/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 12:40:37 by avalsang          #+#    #+#             */
/*   Updated: 2025-03-28 12:40:37 by avalsang         ###   ########.fr       */
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
		printf("%s, ", temp->literal);
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
		c == '|' || c == '$' || \
		c == '(' || c == ')')
		return (1);
	return (0);
}

int	token_quotes(char *str, int *i, t_token *token)
{
	char	c;
	char	*temp;

	c = str[*i];
	temp = str;
	str = ft_strjoin(str, &str[*i]); //make or find one function that does this
	free(temp);
	return (0);
}


// a token that doesn't contain meta characters and isn't quoted is a word
// a token with no quotes and at least one meta character is an operator
int	create_tokens(char *str, t_token **head)
{
	char	*buffer;
	char	*token_start;
	int		i;
	int		j;

	i = 0;
	while (str && str[i])// process the entire line? Or do we break upon newline
	{
		j = 0;
		while (str[i + j] && !is_blank(str[i + j]))
			j ++;
		if (j)
			ft_lstadd_back(head, ft_lstnew(ft_substr(str, i, j)));
		i = i + j + 1;
	}
	print_tokens(head);
	return (0);
}
