/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:20:59 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/15 19:41:26 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	copy_latter_half_of_string(char **result, char *str);
static void	perform_sub(t_data *data, char **str, int i, char *param);
static int	skip_quotes(char **str, int *dquote, int *i);

// loop through the string until you find a dollar sign
// params are not expanded in single quotes or after backslash
// dquote is used to track if we're in a double quote or not
// heredoc expands even in quotes, because why not
void	param_sub(t_data *data, char **str, int heredoc)
{
	int		i;
	int		dquote;
	char	*key;

	i = 0;
	dquote = 0;
	while (*str && (*str)[i])
	{
		if (heredoc == 0 && skip_quotes(str, &dquote, &i))
			continue ;
		if ((*str)[i] == '$')
		{
			key = get_param_name((*str) + i + 1);
			if (!*key && (!(*str)[i + 1] || dquote % 2 != 0))
			{
				i++;
				free(key);
				continue ;
			}
			(perform_sub(data, str, i, key), free(key));
			continue ;
		}
		i++;
	}
}

// helper string, returns the key of an env var
// keys can have alphanum or _ in them, but they cannot start with a num
char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] && (str[i] == '?'))
		return (ft_strndup(str, 1));
	else if (str[i] && (str[i] >= '0' && str[i] <= '9'))
		return (ft_strndup(str, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_strndup(str, i));
}

// helper function for param subbing, used to skip over quotes 
// and track status of double quotes
static int	skip_quotes(char **str, int *dquote, int *i)
{
	if ((*str)[*i] == '\\')
	{
		(*i) += 2;
		return (1);
	}
	if ((*str)[*i] == '\"')
	{
		(*dquote)++;
		(*i)++;
		return (1);
	}
	else if ((*str)[*i] == '\'' && (*dquote % 2) == 0)
	{
		(*i)++;
		while ((*str)[*i] && (*str)[(*i)] != '\'')
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

// function used to replace the $ value
// copy everything before the dollar sign, strjoin it with the sub,
// then strjoin that with the rest of the string
static void	perform_sub(t_data *data, char **str, int i, char *key)
{
	char	*sub_value;
	char	*result;
	char	*temp;

	result = NULL;
	if (*key == '?')
		sub_value = ft_itoa(data->exit_status);
	else
		sub_value = value_envp(&data->env_llst, key);
	result = ft_strndup((*str), i);
	temp = result;
	if (sub_value)
	{
		result = ft_strjoin(temp, sub_value);
		(free(temp), free(sub_value));
	}
	copy_latter_half_of_string(&result, *str + ft_strlen(key) + i + 1);
	if (result)
	{
		free(*str);
		*str = result;
	}
}

static void	copy_latter_half_of_string(char **result, char *str)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(temp, str);
	free(temp);
}
