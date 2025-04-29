

#include "../inc/minishell.h"

static char	*get_param_name(char *str);

static char	*get_param_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

// put me in coach
void	param_sub(t_data *data, char **str)
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
			if (result)
				free(result);
			result = ft_strndup((*str), i - 1);
			param = get_param_name((*str) + 1);
			temp = value_envp(&data->env_llst, param);
			temp2 = result;
			result = ft_strjoin(temp2, temp);
			free(temp2);
			// printf("s= %s\n", temp);
		}
		i++;
	}
	if (result)
	{
		free((*str));
		(*str) = result;
	}
}
