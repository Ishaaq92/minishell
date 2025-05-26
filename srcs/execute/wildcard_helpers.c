/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-17 15:00:38 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-17 15:00:38 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_wildcard(char *str);
static int	find_matches(char *prefix, char *suffix, t_token **wild_args);
static int	check_sequence(char *d_name, char *prefix, char *suffix);

int	get_wildcard_args(t_token *args, t_token **wild_args)
{
	int		j;
	char	*suffix;
	char	*prefix;

	j = 0;
	suffix = find_wildcard(args->literal);
	if (!suffix)
		return (1);
	while (args->literal[j] != '*')
		j++;
	prefix = ft_strndup(args->literal, j++);
	suffix = ft_strdup(++suffix);
	(remove_quotes(prefix), remove_quotes(suffix));
	find_matches(prefix, suffix, wild_args);
	return (free(prefix), free(suffix), 0);
}

static char	*find_wildcard(char *str)
{
	int		i;
	int		quote_char;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (str + i);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			quote_char = str[i++];
			while (str[i] != quote_char)
				i++;
			i++;
		}
		else
			i++;
	}
	return (NULL);
}

static int	find_matches(char *prefix, char *suffix, t_token **wild_args)
{
	DIR				*d;
	struct dirent	*dir;
	t_token			*new;

	d = opendir(".");
	if (!d)
		return (1);
	dir = readdir(d);
	while (dir != NULL)
	{
		if (check_sequence(dir->d_name, prefix, suffix) == 0)
		{
			new = ft_lstnew(ft_strdup(dir->d_name));
			ft_lstadd_back(wild_args, new);
			new->type = WORD;
		}
		dir = readdir(d);
	}
	closedir(d);
	return (0);
}

static int	check_sequence(char *d_name, char *prefix, char *suffix)
{
	int	len;
	int	p_len;
	int	s_len;

	len = ft_strlen(d_name);
	p_len = ft_strlen(prefix);
	s_len = ft_strlen(suffix);
	if (p_len + s_len > len)
		return (1);
	if (ft_strncmp(d_name, prefix, p_len) != 0
		|| ft_strcmp(&d_name[len - s_len], suffix) != 0)
		return (1);
	return (0);
}
