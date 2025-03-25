/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 12:24:22 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-28 12:24:22 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)(big));
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && big[i + j] != '\0' && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
		j = 0;
	}
	return (0);
}
/* 
int main()
{
	char	*test1;
	
	test1 = "test1 Hell test2 Hello test3 test4 World";
	char	*test2 = "Hell";
    printf("strnstr = %s\n", ft_strnstr(test1, test2, 30));

    // printf("strcat = %s\n", strnstr(test1, test2, 30));
    return 0;
}
 */