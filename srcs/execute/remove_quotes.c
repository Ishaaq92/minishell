/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:00:07 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/23 16:41:07 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	collapse_quotes(char *str, int *i, char quote_char);

// loop through the string and find a quote or a backslash
// in bash, quotes are dealt from left to right, not as nested matryoshka dolls
// if a quote is found, the string collapses in on itself, removing the quotes
// everything after the first quote is shifted one char to the left, and same
// for after the second quote
void	remove_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			collapse_quotes(str, &i, str[i]);
		else if (str[i] == '\"')
			collapse_quotes(str, &i, str[i]);
		else if (str[i] == '\\')
		{
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
			i++;
		}
		else
			i++;
	}
}

// helper function to remove quotes
// the quote char is used to diffentiate between single and double quote
static void	collapse_quotes(char *str, int *i, char quote_char)
{
	ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] != '\0')
		ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
}
