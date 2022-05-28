/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:41:08 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:41:09 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_num(const char *s, int *flag, int min)
{
	unsigned long long int	number;

	number = 0;
	while (*s >= '0' && *s <= '9')
	{
		number = number * 10 + *s - '0';
		s++;
	}
	if ((number > 9223372036854775807 && min == 0)
		|| (number > 9223372036854775808U && min == 1) || ft_strlen(s) > 19)
		*flag = 1;
	return (number);
}

static long long int	atoi_mod(char *str, int *flag)
{
	long long int	number;
	int				min;

	min = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!((*str >= '0' && *str <= '9') || *str == '+' || *str == '-'))
		return (0);
	if ((*str == '+' || *str == '-') && \
		!(*(str + 1) >= '0' && (*(str + 1) <= '9')))
		return (0);
	if (*str == '-')
	{
		min = 1;
		str++;
	}
	if (*str == '+')
		str++;
	number = ft_num(str, flag, min);
	if (min == 1)
		number = -number;
	return (number);
}

static void	print_error_exit(char *data)
{
	ft_putstr_fd("bash: exit ", 2);
	ft_putstr_fd(data, 2);
	ft_putendl_fd(": numeric argument required", 2);
	g_return_code = 255;
}

void	exit_build_in(t_cmd *s)
{
	long long int	num;
	int				check;
	int				flag;

	flag = 0;
	if (s->num == 0)
		ft_putendl_fd("exit", 1);
	if (!s->cmd[1])
		exit_minishell();
	check = check_if_str_num(s->cmd[1]);
	num = atoi_mod(s->cmd[1], &flag);
	if (!check || (check && !s->cmd[2] && flag == 1))
		print_error_exit(s->cmd[1]);
	else if (check && s->cmd[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		g_return_code = 1;
		return ;
	}
	else if (check && !s->cmd[2] && flag == 0)
		g_return_code = num % 256;
	exit(g_return_code);
}
