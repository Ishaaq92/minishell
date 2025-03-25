/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 15:12:42 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-22 15:12:42 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pipex_perror(void)
{
	perror("pipex");
}

void	custom_error(char *str, char *msg, int errnum, t_data *data)
{
	write(2, "pipex: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->error = errnum;
}
