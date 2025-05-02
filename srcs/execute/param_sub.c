/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 16:20:59 by avalsang          #+#    #+#             */
/*   Updated: 2025-04-30 16:20:59 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_param_name(char *str);
void	copy_latter_half_of_string(char **result, char *str);

static char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_strchr(" =\"\'\\", str[i]))
		i++;
	return (ft_strndup(str, i));
}

// put me in coach
void	param_sub_2(t_data *data, char **str)
{
	int		i;
	char	*result;
	char	*sub_str;
	char	*temp;
	char	*temp2;
	char	*param;

	i = 0;
	result = NULL;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				printf("exit status = %i\n", data->exit_status);
				i++;
				continue ;
			}
			if (result)
				free(result);
			result = ft_strndup((*str), i - 1);
			param = get_param_name((*str) + 1);
			temp = value_envp(&data->env_llst, param);
			temp2 = result;
			result = ft_strjoin(temp2, temp);
			free(temp2);
		}
		i++;
	}
	if (result)
	{
		free((*str));
		(*str) = result;
	}
}

void	perform_sub(t_data *data, char **str, int i)
{
	char	*sub_value;
	char	*result;
	char	*param;
	char	*temp;

	result = NULL;
	param = get_param_name((*str) + i + 1);
	sub_value = value_envp(&data->env_llst, param);
	if (sub_value)
	{
		result = ft_strndup((*str), i - 1);
		temp = result;
		result = ft_strjoin(temp, sub_value);
		free(temp);
		copy_latter_half_of_string(&result, *str + ft_strlen(param) + i + 1);
	}
	if (result)
	{
		free(*str);
		*str = result;
	}
	free(param);
}

void	copy_latter_half_of_string(char **result, char *str)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(temp, str);
	free(temp);
	// printf("latter half of strin = %s\n", str);
}

void	param_sub(t_data *data, char **str)
{
	int		i;

	i = 0;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				// set exit code here
				i++;
				continue ;
			}
			perform_sub(data, str, i);
		}
		i++;
	}
}