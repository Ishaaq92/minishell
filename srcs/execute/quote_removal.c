
#include "../../inc/minishell.h"

// it can't be this easy... what have I missed?
// uncomment the main, and compile with:
// cc quote_removal.c -L ../../Libft/ -lft

void	remove_quotes(char *str);
void	collapse_quotes(char *str, int *i, char quote_char);

void	remove_quotes(char *str)
{
	int		i;
	int		end_quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			collapse_quotes(str, &i, str[i]);
		}
		else if (str[i] == '\"')
		{
			collapse_quotes(str, &i, str[i]);
		}
		else if (str[i] == '\\')
		{
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
		}
		i++;
	}
}

void	collapse_quotes(char *str, int *i, char quote_char)
{
	ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (str[*i] != '\0')
	{
		ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
	}
}

// #include <stdio.h>
// int main()
// {
// 	char *test;

// 	test = ft_strdup("\'hello\' \'world\' \\a \\b");
// 	printf("test = %s\n", test);
// 	remove_quotes(test);
// 	printf("result = %s\n", test);
// 	free(test);

// 	return (0);
// }
