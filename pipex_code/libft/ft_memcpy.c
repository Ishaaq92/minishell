/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 16:58:36 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 16:58:36 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h>
int	main (void)
{
	char arr[5];
	const char *s = "aaa";
	memcpy(arr, s, sizeof(arr));
	printf("orig = %s\n", arr);

	ft_memcpy(arr, s, sizeof(arr));
	printf("myfunc = %s\n", arr);
}
 */