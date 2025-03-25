/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 15:12:13 by avalsang          #+#    #+#             */
/*   Updated: 2025-02-22 15:12:13 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*split_buffer(char **line, char *buffer, size_t len)
{
	size_t		i;
	size_t		j;
	char		*temp;

	i = find_newline(*line) + 1;
	if (i == 0)
		i = len;
	buffer = ft_strdup(*line + i);
	temp = *line;
	*line = ft_calloc(i + 1, sizeof(char));
	if (*line == NULL)
		return (free(buffer), NULL);
	j = 0;
	while (temp[j] && temp[j] != '\n')
	{
		(*line)[j] = temp[j];
		j++;
	}
	if (temp[j] && temp[j] == '\n')
		(*line)[j++] = '\n';
	(*line)[j] = '\0';
	return (free(temp), buffer);
}

char	*read_until_newline(int fd, char *line, size_t *len)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		*len += bytes_read;
		temp = line;
		line = gnl_strjoin(temp, buffer, *len);
		free(temp);
		temp = NULL;
		if (find_newline(buffer) != -1)
			break ;
	}
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;
	size_t			output_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	output_len = 0;
	if (buffer)
	{
		line = ft_strdup(buffer);
		output_len = ft_strlen(buffer);
		free(buffer);
	}
	else
		line = ft_strdup("");
	line = read_until_newline(fd, line, &output_len);
	if (line == NULL || *line == '\0')
		return (free(buffer), free(line), NULL);
	buffer = split_buffer(&line, buffer, output_len);
	if (buffer && *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
