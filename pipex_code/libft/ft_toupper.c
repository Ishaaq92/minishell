/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 17:38:20 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 17:38:20 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 122 && c >= 97)
		return (c - 32);
	else
		return (c);
}
/* 
#include <stdio.h>
#include <ctype.h>
int	main (void)
{
	char s = 'a';
	printf("myfunc = %c\n", ft_toupper(s));
	printf("orig = %c", toupper(s));
}
 */