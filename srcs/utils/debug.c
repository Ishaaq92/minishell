/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:10:15 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:10:15 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// prints the token list, along with token type enum, for debugging purposes
void	print_tokens(t_token **head)
{
	t_token		*temp;

	temp = *head;
	printf("tokens: {");
	while (temp != NULL)
	{
		printf("%s[%i], ", temp->literal, temp->type);
		temp = temp->next;
	}
	printf("}\n");
}
