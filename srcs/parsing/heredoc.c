/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-19 13:43:53 by avalsang          #+#    #+#             */
/*   Updated: 2025-05-19 13:43:53 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_lim_for_quotes(char *str);
static int	store_input(t_data *data, char *lim, char *temp_name);
static void	write_buffer(char *buffer, int temp_fd);

// crawl through the token list, look for heredoc tokens
// the next token was the limiter for heredoc, which we don't need anymore
// so replace that token with the name of the temp file created so exec and 
// ast can access the file
int	parse_heredoc(t_data *data, t_token *token)
{
	char	*temp_name;
	int		i;
	char	*temp_no;

	i = 0;
	while (token)
	{
		if (token->type == IN_HEREDOC)
		{
			temp_no = ft_itoa(i);
			temp_name = ft_strjoin("temp_", temp_no);
			if (store_input(data, token->next->literal, temp_name))
				return (free(temp_no), free(temp_name), 1);
			(free(token->next->literal), free(temp_no));
			token->next->literal = temp_name;
			i++;
		}
		token = token->next;
	}
	return (0);
}

// begins the heredoc user prompt, stores input in a temp file
static int	store_input(t_data *data, char *lim, char *temp_name)
{
	char	*buffer;
	int		has_quotes;
	int		temp_fd;

	has_quotes = check_lim_for_quotes(lim);
	remove_quotes(lim);
	temp_fd = open(temp_name, O_CREAT | O_WRONLY | O_TRUNC | O_RDONLY, 0666);
	if (temp_fd < 0)
		return (custom_error("open", "failed to open temp file"), 1);
	while (lim)
	{
		buffer = readline("> ");
		if (buffer && !ft_strcmp(buffer, lim))
			break ;
		if (!has_quotes)
			param_sub(data, &buffer, 1);
		(write_buffer(buffer, temp_fd), free(buffer));
	}
	return (free(buffer), close(temp_fd), 0);
}

static void	write_buffer(char *buffer, int temp_fd)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\\' && ft_strchr("$\\", buffer[i + 1]))
		{
			write(temp_fd, buffer + i + 1, 1);
			i += 2;
		}
		else
			write(temp_fd, buffer + i++, 1);
	}
	write(temp_fd, "\n", 1);
}

// if the limiter token after heredoc contains any quote or backslash,
// do not perform paramter expansion on heredoc input
static int	check_lim_for_quotes(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_strchr("\"\'\\", *str))
			return (1);
		str++;
	}
	return (0);
}
