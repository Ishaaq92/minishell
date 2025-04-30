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

// it can't be this easy... what have I missed?
// uncomment the main, and compile with:
// cc quote_removal.c -L ../../Libft/ -lft

static void	collapse_quotes(char *str, int *i, char quote_char);

void	remove_quotes(char *str)
{
	int		i;
	int		end_quote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			collapse_quotes(str, &i, str[i]);
		else if (str[i] == '\"')
			collapse_quotes(str, &i, str[i]);
		else if (str[i] == '\\')
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
	}
}

static void	collapse_quotes(char *str, int *i, char quote_char)
{
	ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] != '\0')
		ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
}
