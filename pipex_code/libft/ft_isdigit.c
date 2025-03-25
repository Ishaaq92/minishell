/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 16:26:28 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 16:26:28 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (c);
	return (0);
}
/* 
#include <stdio.h>
#include <ctype.h>
int	main (void)
{
	printf("orig = %i\n", ft_isdigit('1'));
	printf("orig = %i", isdigit('1'));
}
 */