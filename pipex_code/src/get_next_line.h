/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:40:12 by abhi              #+#    #+#             */
/*   Updated: 2025/02/21 17:40:15 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	*ft_calloc(size_t nmemb, size_t size);
ssize_t	find_newline(char *str);
size_t	ft_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2, size_t len);
char	*ft_strdup(const char *src);

char	*split_buffer(char **line, char *buffer, size_t len);
char	*read_until_newline(int fd, char *line, size_t *len);
char	*get_next_line(int fd);
#endif
