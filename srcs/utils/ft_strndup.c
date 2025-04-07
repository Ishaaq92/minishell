/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-04 16:06:33 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-04 16:06:33 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*duplicate;

	i = 0;
	duplicate = malloc(sizeof(char) * (n + 1));
	if (!duplicate)
		return (NULL);
	while (s[i] && i < n)
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = 0;
	return (duplicate);
}
