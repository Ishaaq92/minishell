/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:21:34 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/14 18:50:18 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int print_files(char *prefix, char *suffix);

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
		printf("%s\n", dir->d_name);
	closedir(d);
	return(0);
}

static void	check_sequence(char *d_name)
{

}