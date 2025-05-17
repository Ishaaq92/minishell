/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:21:34 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/16 12:01:46 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int 		print_files(char *prefix, char *suffix, t_token **wild_args);
static int	check_sequence(char *d_name, char *prefix, char *suffix);
int			count_files(char *prefix, char *suffix);
void		join_list(t_token *args, t_token *wild);
int			get_wildcard_args(t_token *args, t_token **wild_args);

void    wildcards(t_data *data)
{
	t_token		*args;
	t_token		*wild_args;
	t_token		*temp;

	args = data->token_list;
	wild_args = NULL;
	while (args)
	{
		if (get_wildcard_args(args, &wild_args) != 0)
		{
			args = args ->next;
			continue ;
		}	
		join_list(args, wild_args);
		temp = args;
		args = args->next;
		if (wild_args)
		{
			ft_lstdelone(temp);
			wild_args = NULL;
		}
	}
}

void	join_list(t_token *args, t_token *wild)
{
	t_token		*temp;
	t_token		*wild_args_last;

	if (wild)
	{
		temp = args->prev;
		temp->next = wild;
		wild->prev = temp;
		wild_args_last = ft_lstlast(wild);
		wild_args_last->next = args->next;
		temp = args->next;
		if (temp)
			temp->prev = wild_args_last;
	}
}

void	ft_lstdelone(t_token *args)
{
	if (args->literal)
		free(args->literal);
	free(args);
}

int	get_wildcard_args(t_token *args, t_token **wild_args)
{
	int		j;
	char	*suffix;
	char	*prefix;

	j = 0;
	suffix = ft_strchr(args->literal, '*');
	if (!suffix)
		return (1);
	while (args->literal[j] != '*')
		j++;
	prefix = ft_strndup(args->literal, j++);
	suffix = ft_strdup(++suffix);
	print_files(prefix, suffix, wild_args);
	return (free(prefix), free(suffix), 0);
}

int print_files(char *prefix, char *suffix, t_token **wild_args) 
{
	DIR				*d;
	struct dirent	*dir;
	t_token			*new;

	d = opendir(".");

	if (!d)
		return (1);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] == '.')
			continue ;
		if (check_sequence(dir->d_name, prefix, suffix) == 0)
		{
			new = ft_lstnew(ft_strdup(dir->d_name));
			ft_lstadd_back(wild_args, new);
			new->type = WORD;
			// printf("%s\n", dir->d_name);
		}
	}
	closedir(d);
	return(0);
}

int count_files(char *prefix, char *suffix) 
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	d = opendir(".");
	count = 0;
	if (!d)
		return (1);
	while ((dir = readdir(d)) != NULL)
	{
		if (check_sequence(dir->d_name, prefix, suffix) == 0)
			count ++;
	}
	closedir(d);
	// printf("%d", count);
	return(count);
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
	if (ft_strncmp(d_name, prefix, p_len) != 0 || ft_strcmp(&d_name[len - s_len], suffix) != 0)
		return (1);
	return (0);
}
