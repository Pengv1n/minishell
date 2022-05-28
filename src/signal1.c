/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:08:06 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:08:08 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	handle_sigint_fork(void)
{
	write(2, "\n", 1);
}

void	handle_sigquit_fork(void)
{
	write(2, "Quit: 3\n", 9);
}

void	signal_for_main_with_fork(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *) handle_sigint_fork);
	signal(SIGQUIT, (void *) handle_sigquit_fork);
}
