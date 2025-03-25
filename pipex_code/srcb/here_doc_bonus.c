/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 15:12:28 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-22 15:12:28 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

// if argv[1] is here_doc, replace infile with stdinput
// read with gnl until buffer == lim
void	here_doc(char *lim, t_data *data)
{
	int		fd;
	char	*buffer;

	if (lim == NULL || (lim && *lim == '\0'))
	{
		custom_error("LIMITER", "No limiter specified", 1, data);
		(free_data(data), exit(1));
	}
	fd = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		pipex_perror();
	while (1)
	{
		write(1, "> ", 2);
		buffer = get_next_line(0);
		if (buffer == NULL)
			break ;
		if (ft_strncmp(buffer, lim, ft_strlen(buffer) - 1) == 0)
			break ;
		(write(fd, buffer, ft_strlen(buffer)), free(buffer));
	}
	(free(buffer), close(fd));
	data->in_fd = open("temp", O_RDONLY);
	if (data->in_fd == -1)
		(free_data(data), exit(1));
}
