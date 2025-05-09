/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:20:59 by avalsang          #+#    #+#             */
/*   Updated: 2025/05/06 15:40:05 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_param_name(char *str);
static void	copy_latter_half_of_string(char **result, char *str);
static void	perform_sub(t_data *data, char **str, int i, char *param);

static char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] && str[i] == '?')
		i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (ft_strndup(str, i));
}

void	skip_quotes(t_data *data, char **str, int *dquote, int *i)
{
	if ((*str)[*i] == '\"')
		(*dquote)++;
	if ((*str)[*i] == '\'')
	{
		(*i)++;
		while ((*str)[(*i)] != '\'' && (*dquote % 2) == 0)
			(*i)++;
	}
}

// put me in coach
void	param_sub(t_data *data, char **str)
{
	int		i;
	int		dquote;
	char	*key;
	

	i = 0;
	dquote = 0;
	while (*str && (*str)[i])
	{
		skip_quotes(data, str, &dquote, &i);
		if ((*str)[i] == '$')
		{
			key = get_param_name((*str) + i + 1);
			perform_sub(data, str, i, key);
		}
		i++;
	}
}

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
		free(temp);
	}
	copy_latter_half_of_string(&result, *str + ft_strlen(key) + i + 1);
	if (result)
	{
		free(*str);
		*str = result;
	}
	free(key);
}

static void	copy_latter_half_of_string(char **result, char *str)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(temp, str);
	free(temp);
}
