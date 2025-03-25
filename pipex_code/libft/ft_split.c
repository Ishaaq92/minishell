/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-02 13:46:43 by avalsang          #+#    #+#             */
/*   Updated: 2024-12-02 13:46:43 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(const char *str, char sep)
{
	int	i;
	int	words;
	int	in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != sep && in_word == 0)
		{
			in_word = 1;
			words++;
			while (str[i] && str[i] != sep)
				i++;
		}
		else if (str[i] == sep)
		{
			in_word = 0;
			i++;
		}
	}
	return (words);
}

static int	word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !check_sep(str[i], c))
		i++;
	return (i);
}

static char	*ft_strdup_split(const char *str, char c)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = word_len(str, c);
	word = (char *) malloc (sizeof(char) * (len + 1));
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (s == NULL || result == NULL || count_words(s, c) == 0)
		return (free(result), NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = ft_strdup_split(s, c);
			while (*s && *s != c)
				s++;
			i++;
		}
		else
			s++;
	}
	result[i] = 0;
	return (result);
}

/* 
int	main(void)
{
	char	**res;
	int i = 0;
	char arr[] = "   lorem   ipsum ";
	char sep = ' ';
	res = ft_split(arr, sep);
	printf("words = %i\n", count_words(arr, sep));
	while (i <= count_words(arr, ' '))
	 	printf("res = %s\n", res[i++]);
	return (0);
}
 */