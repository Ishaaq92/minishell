/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-02 13:36:10 by avalsang          #+#    #+#             */
/*   Updated: 2024-12-02 13:36:10 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(long n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digits;
	long	num;

	num = n;
	if (num == 0)
		return (ft_strdup("0"));
	digits = get_digits(num);
	result = (char *)malloc(sizeof(char) * (digits + 1));
	if (result == NULL)
		return (NULL);
	result[digits--] = '\0';
	if (num < 0)
	{
		num *= -1;
		result[0] = '-';
	}
	while (num > 0)
	{
		result[digits--] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
/* 
#include <stdio.h>
int main()
{
	char *s = ft_itoa(-0);
	printf("s = %s\n", s);
}
 */