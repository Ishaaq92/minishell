/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-28 14:54:14 by avalsang          #+#    #+#             */
/*   Updated: 2024-11-28 14:54:14 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		minus;
	int		result;

	i = 0;
	minus = 0;
	result = 0;
	while ((str[i] <= '\r' && str[i] >= '\t') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		minus = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (minus == 1)
		result = -result;
	return (result);
}
/*  
#include <stdio.h>
int main()
{

	printf("ft_atoi = %i\n", ft_atoi("\n\t\r\f\v \t+42a432"));
	printf("original = %i\n", atoi("\n\t\r\f\v \t+42a432"));
	return (0);
}
 */