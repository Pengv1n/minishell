/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:04:22 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:05:11 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int n, char *str)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_return_code = errno;
	}
	else if (n == 2)
	{
		g_return_code = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(EXIT_FAILURE);
}

void	error_with_std_function(int n)
{
	if (n >= 1 && n <= 15)
		ft_putstr_fd("error with malloc\n", 2);
	if (n == 20)
		ft_putstr_fd("Error: can't create a pipe\n", 2);
	if (n == 21)
		ft_putstr_fd("Can't make a fork\n", 2);
	exit (n);
}

void	exit_minishell(void)
{
	if (WIFSIGNALED(g_return_code))
		exit(1);
	exit(EXIT_SUCCESS);
}

t_list	*error_ambitious_data(t_list *cmd_data, t_cmd *s)
{
	s->err = 1;
	s->cmd = NULL;
	printf("minishell: %s: ambiguous redirect\n", cmd_data->amb_data);
	g_return_code = 1;
	while (cmd_data && !data_is_pipe(cmd_data))
		cmd_data = cmd_data->next;
	return (cmd_data);
}

t_list	*error_with_redirect(t_list *cmd_data, t_cmd *s)
{
	printf("minishell: %s: %s\n", cmd_data->next->content, strerror(errno));
	s->cmd = NULL;
	s->err = 1;
	while (cmd_data && !data_is_pipe(cmd_data))
		cmd_data = cmd_data->next;
	return (cmd_data);
}
