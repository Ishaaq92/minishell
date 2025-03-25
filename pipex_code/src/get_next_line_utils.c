/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-09 12:46:23 by avalsang          #+#    #+#             */
/*   Updated: 2025-01-09 12:46:23 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	n;
	size_t	i;

	if (nmemb == 0 || size == 0)
		n = 1;
	else
		n = nmemb * size;
	ptr = malloc(n);
	i = 0;
	if (ptr != NULL)
	{
		while (i < n)
			((char *)ptr)[i++] = '\0';
	}
	return (ptr);
}

ssize_t	find_newline(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

char	*gnl_strjoin(char *s1, char *s2, size_t len)
{
	char	*output;
	char	*tmp;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	output = (char *) malloc((len + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	tmp = output;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (output);
}

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		len;
	size_t		i;

	len = 0;
	while (src[len] != '\0')
		len++;
	dest = (char *) malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
