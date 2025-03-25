/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 14:36:47 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-17 14:36:47 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// test this function, see if it works for file and dir correctly
int	check_dir(char *argv)
{
	int	fd;

	fd = open(argv, __O_DIRECTORY);
	if (fd != -1)
	{
		pipex_perror();
		close(fd);
		return (1);
	}
	return (0);
}

void	init_struct(t_data *data, int argc)
{
	data->argc = argc;
	data->in_fd = 0;
	data->out_fd = 0;
	data->error = 0;
	data->here_doc = 0;
	data->last_cmd = 0;
	data->last_pid = 0;
	data->cmd_list = NULL;
	data->env_paths = NULL;
}

// open infile and outfile, check for existence, permission, 
// and if its a directory
// infile checks for all three, 
// outfile skips out on existence, is created if not found
void	open_infile(t_data *data, char **argv)
{
	data->in_fd = open(argv[1], O_RDONLY);
	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
		custom_error(argv[1], strerror(errno), errno, data);
	if (data->in_fd == -1)
		data->in_fd = open("/dev/null", O_RDONLY);
}

void	init_outfile(t_data *data, int argc, char **argv)
{
	if (data->here_doc == 1)
	{
		data->out_fd = open(argv[argc - 1],
				O_CREAT | O_WRONLY | O_APPEND, 0666);
		check_dir(argv[argc - 1]);
		if (access(argv[argc - 1], W_OK) == -1)
			return (close(data->out_fd), pipex_perror(),
				free_data(data), exit(1));
	}
	else
	{
		data->out_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		check_dir(argv[argc - 1]);
		if (access(argv[argc - 1], W_OK) == -1)
			return (close(data->out_fd), pipex_perror(),
				free_data(data), exit(1));
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}
