/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:21:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/04/07 17:33:08 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	write(1, "Control C was inputed\n", 23);
	exit_cleanup();
	return ;
}

void	handle_ctrl_z(int sig)
{
	write(1, "Control Z was inputed\n", 23);
	exit_cleanup();
	return ;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGTSTP, handle_ctrl_z);
}
