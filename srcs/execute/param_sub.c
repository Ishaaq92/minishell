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
static void	copy_latter_half_of_string(char **result, char *str);
static void	perform_sub(t_data *data, char **str, int i, char *param);

static char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_strchr(" =\"\'\\", str[i]))
		i++;
	return (ft_strndup(str, i));
}

// put me in coach
void	param_sub(t_data *data, char **str)
{
	int		i;
	char	*param;

	i = 0;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				param = ft_itoa(data->exit_status);
				perform_sub(data, str, i, param);
				i++;
				continue ;
			}
			param = get_param_name((*str) + i + 1);
			perform_sub(data, str, i, param);
		}
		i++;
	}
}

static void	perform_sub(t_data *data, char **str, int i, char *param)
{
	char	*sub_value;
	char	*result;
	char	*temp;

	result = NULL;
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

static void	copy_latter_half_of_string(char **result, char *str)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(temp, str);
	free(temp);
}
