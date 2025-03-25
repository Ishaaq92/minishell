/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 17:15:15 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-26 17:15:15 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memmove will pick between forwards and backwards copy,
// if it detects overlap, it will opt for a backwards copy.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (dest_ptr > src_ptr)
	{
		dest_ptr += (n - 1);
		src_ptr += (n - 1);
		while (n-- > 0)
			*dest_ptr-- = *src_ptr--;
	}
	else
		return (ft_memcpy(dest_ptr, src_ptr, n));
	return (dest);
}

/* 
int main()
{
	char x[] = "abcdefghi";
	memmove(&x[3], &x[0], 6);
	printf("after memmove: %s\n", x);

	char y[] = "abcdefghi";
	memcpy(&y[3], &y[0], 6);
	printf("after memcpy:  %s\n", y);

	printf("\n");
	strcpy(x, "abcdefghi");
	ft_memmove(&x[3], &x[0], 6);
	printf("after ft_memmove: %s\n", x);

	strcpy(y, "abcdefghi");
	ft_memcpy(&y[3], &y[0], 6);
	printf("after ft_memcpy:  %s\n", y);
}
 */
/* 
int main()
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	int		arg;

	dest = src + 1;
	ft_memmove(src, dest, 8);
	write(1, dest, 22);
}
 */