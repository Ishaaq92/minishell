/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:34 by avalsang          #+#    #+#             */
/*   Updated: 2024/07/17 14:42:36 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		word_len(char *str, char *charset);
static int		check_sep(char c, char *charset);
static int		count_words(char *str, char *charset);
static char		*ft_strdup_split(char *str, char *charset);

char	**ft_split2(char *str, char *charset)
{
	char	**result;
	int		i;

	result = malloc ((count_words(str, charset) + 1) * sizeof(char *));
	if (result == NULL || str == NULL || count_words(str, charset) == 0)
		return (free(result), NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str && check_sep(*str, charset))
			str++;
		if (*str)
			result[i++] = ft_strdup_split(str, charset);
		while (*str && !check_sep(*str, charset))
			str++;
	}
	result[i] = 0;
	return (result);
}

static int	word_len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !check_sep(str[i], charset))
		i++;
	return (i);
}

static int	check_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (check_sep(str[i + 1], charset))
			if (check_sep(str[i], charset) == 0)
				words++;
		i++;
	}
	return (words);
}

static char	*ft_strdup_split(char *str, char *charset)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = word_len(str, charset);
	word = (char *) malloc (sizeof(char) * len + 1);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/* 
#include <stdio.h>
int	main(void)
{
	char	**res;
	char *arr;
	char *sep;
	int i = 0;
	sep = (char *) malloc (50000 * sizeof(char));
	arr = (char *) malloc (50000 * sizeof(char));
	arr = "word1 word2 word3 word4 !";
	sep = " ";
	res = ft_split(arr, sep);
	printf("words = %i\n", count_words(arr, sep));
	while (i <= count_words(arr, sep))
		printf("res = %s\n", res[i++]);
	return (0);
}
 */