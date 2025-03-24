/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:19:35 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/24 14:52:41 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include "../Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

enum e_commands
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
};

#endif