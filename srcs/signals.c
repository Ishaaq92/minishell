/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:21:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/03/25 15:27:59 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	write(0, "\n", 1);
	return ;
}

void	handle_ctrl_z(int sig)
{
	write(1, "Control Z was inputed\n", 1);
	exit_cleanup();
	return ;
}
void	handle_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGTSTP, handle_ctrl_z);
}