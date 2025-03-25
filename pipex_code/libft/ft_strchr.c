/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-02 13:47:01 by avalsang          #+#    #+#             */
/*   Updated: 2024-12-02 13:47:01 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
/* 
int	main()
{
	char *arr = "abcde";
	char *c = ft_strchr(arr, '\0');
	printf("pointer = %p\n", &arr[5]);
	printf("pointer = %p\n", c);
	printf("char = %c", *c);
}
 */