/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:21:20 by isahmed           #+#    #+#             */
/*   Updated: 2025/05/21 19:41:46 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	g_sig = 0;

void	set_signal(int sig)
{
	g_sig = sig;
}

int	get_signal(void)
{
	return (g_sig);
}

void	handle_ctrl_c(int sig)
{
	set_signal(sig);
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
}

void	handle_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
