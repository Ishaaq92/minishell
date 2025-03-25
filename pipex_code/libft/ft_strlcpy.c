/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 17:36:50 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 17:36:50 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/* 
#include <stdio.h>
#include <bsd/string.h>
// use flag -lbsd when compiling
int main()
{
    char src[] = "Hello12334";
    char dest[] = "World";

    printf("Length of src = %zu\n", ft_strlcpy(dest, src, 8));
    printf("Dest string after function call = %s\n", dest);

	char src1[] = "Hello12334";
    char dest1[] = "World";
    printf("Length of src = %zu\n", strlcpy(dest1, src1, 8));
	printf("Dest string after function call = %s\n", dest);
    return 0;
}
 */