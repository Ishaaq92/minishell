/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 16:47:30 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 16:47:30 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/* 
#include <stdio.h>
#include <string.h>
int	main (void)
{
	char arr[5];
	bzero(arr, sizeof(arr));
	printf("orig = %s\n", arr);

	ft_bzero(arr, sizeof(arr));
	printf("orig = %s\n", arr);
}
 */