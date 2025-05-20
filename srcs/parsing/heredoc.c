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
		if (buffer && buffer[0] != '\n'
			&& !ft_strncmp(buffer, lim, ft_strlen(buffer) - 1))
			break ;
		if (!has_quotes)
			param_sub(data, &buffer, 1);
		(write(temp_fd, buffer, ft_strlen(buffer)), free(buffer));
		write(temp_fd, "\n", 1);
	}
	return (free(buffer), close(temp_fd), 0);
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
