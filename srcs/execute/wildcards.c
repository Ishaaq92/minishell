/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:21:34 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/14 19:16:02 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int print_files(char *prefix, char *suffix);
static int	check_sequence(char *d_name, char *prefix, char *suffix);

void    wildcards(t_data *data, t_ast *node)
{
	char    **args;
	char	*prefix;
	char	*suffix;
	int     i;
	int     j;

	i = 0;
	args = node->literal;
	while (args[++i] != NULL)
	{
		j = 0;
		suffix = ft_strchr(args[i], '*');
		if (suffix == 0)
			continue ;
		while (args[i][j] != '*')
			j++;
		prefix = ft_strndup(args[i], j++);
		suffix = ft_strdup(++suffix);
		printf("wildcard!\n");
		printf("before = %s\n", prefix);
		printf("after = %s\n", suffix);
		print_files(prefix, suffix);
	}
}

int print_files(char *prefix, char *suffix) 
{
	DIR *d;
	struct dirent *dir;

	d = opendir(".");
	if (!d)
		return (1);
	while ((dir = readdir(d)) != NULL)
	{
		if (check_sequence(dir->d_name, prefix, suffix) == 0)
			printf("%s\n", dir->d_name);
	}
	closedir(d);
	return(0);
}

static int	check_sequence(char *d_name, char *prefix, char *suffix)
{
	int	len;

	if (ft_strlen(prefix) + ft_strlen)
	printf("here\n");
	len = ft_strlen(prefix);
	printf("%d, ", len);
	if (ft_strncmp(d_name, prefix, len) != 0)
		return (1);
	len = ft_strlen(d_name) - ft_strlen(suffix);
	printf("%d\n", len);
	if (ft_strcmp(&d_name[len], suffix) != 0)
		return (1);
	return (0);
}