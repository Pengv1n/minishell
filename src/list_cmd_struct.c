/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:53:02 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:53:03 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_amount_list(t_list *cmd_data)
{
	int	i;

	i = 1;
	while (cmd_data)
	{
		if (!ft_strncmp(cmd_data->content, "|", 2) && !cmd_data->flag_in_quotes)
			i++;
		cmd_data = cmd_data->next;
	}
	return (i);
}

t_cmd	*end_list_cmd(t_cmd *s)
{
	while (s->next)
		s = s->next;
	return (s);
}

void	add_back_list_cmd(t_cmd **s, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*s)
		*s = new;
	else
	{
		tmp = end_list_cmd(*s);
		tmp->next = new;
		new->next = NULL;
	}
}

t_cmd	*list_cmd_new(int num)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
	{
		ft_putstr_fd("Error malloc\n", 2);
		exit(EXIT_FAILURE);
	}
	new->in = 0;
	new->out = 1;
	new->hr_name = NULL;
	new->num = num;
	new->cmd = NULL;
	new->err = 0;
	new->next = NULL;
	return (new);
}

int	init_cmd_struct(t_list *cmd_data, t_cmd **s, t_msh *msh)
{
	int	amount;
	int	i;

	i = 0;
	amount = check_pipe_amount_list(cmd_data);
	msh->amount = amount;
	while (amount-- && ++i)
		add_back_list_cmd(s, list_cmd_new(i - 1));
	return (1);
}
