/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:08:39 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:08:40 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_echo(char **command, int a, int *flag)
{
	if (command[a] && !ft_strncmp(command[a], "-n", 3))
	{
		*flag = 1;
		a++;
	}
	while (command[a] && !ft_strncmp(command[a], "-n", 3))
		a++;
	return (a);
}

void	echo_build_in(t_cmd *s)
{
	char	**command;
	int		a;
	int		flag;

	flag = 0;
	command = s->cmd;
	a = 1;
	if (!command[a])
		write(s->out, "\n", 1);
	else
	{
		a = for_echo(command, a, &flag);
		while (command[a] && command[a + 1])
		{
			ft_putstr_fd(command[a], s->out);
			write(s->out, " ", 1);
			a++;
		}
		ft_putstr_fd(command[a], s->out);
		if (!flag)
			write(s->out, "\n", 1);
	}
	g_return_code = 0;
}
