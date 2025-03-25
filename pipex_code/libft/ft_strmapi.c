/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-02 13:36:38 by avalsang          #+#    #+#             */
/*   Updated: 2024-12-02 13:36:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*func;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	func = (char *)malloc(sizeof(char) * (len + 1));
	if (func == NULL || s == NULL)
		return (NULL);
	while (i < len)
	{
		func[i] = (*f)(i, s[i]);
		i++;
	}
	func[len] = '\0';
	return (func);
}
