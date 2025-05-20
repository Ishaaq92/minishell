/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:21:34 by ishaaq            #+#    #+#             */
/*   Updated: 2025/05/19 20:29:34 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	join_list(t_token *args, t_token *wild);

void	wildcards(t_data *data)
{
	t_token		*args;
	t_token		*wild_args;
	t_token		*temp;

	args = data->token_list;
	wild_args = NULL;
	while (args)
	{
		if (get_wildcard_args(args, &wild_args))
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

static void	join_list(t_token *args, t_token *wild)
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

// not using this anywhere atm
// int	count_files(char *prefix, char *suffix)
// {
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				count;

// 	d = opendir(".");
// 	count = 0;
// 	if (!d)
// 		return (1);
// 	dir = readdir(d);
// 	while (dir != NULL)
// 	{
// 		if (check_sequence(dir->d_name, prefix, suffix) == 0)
// 			count ++;
// 		dir = readdir(d);
// 	}
// 	closedir(d);
// 	return (count);
// }
