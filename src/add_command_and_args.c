/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_and_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:43:13 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 17:43:29 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_error_process(t_list *cmd_data, t_cmd *s)
{
	s->cmd = NULL;
	while (cmd_data && !data_is_pipe(cmd_data))
		cmd_data = cmd_data->next;
	return (cmd_data);
}

int	count_amount_of_args(t_list *cmd_data)
{
	int	amount;

	amount = 0;
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (cmd_data && data_redirect_and_heredoc(cmd_data))
			cmd_data = cmd_data->next->next;
		else
		{
			if ((cmd_data->flag_dollar_expanded && (*(cmd_data->content)))
				|| !(cmd_data->flag_dollar_expanded))
				amount++;
			cmd_data = cmd_data->next;
		}
	}
	if (!cmd_data && !amount)
		return (-1);
	if (cmd_data && !amount)
		return (-2);
	return (amount);
}

t_list	*skip_pipe_data(t_list *cmd_data, int amount, t_cmd *s)
{
	s->cmd = NULL;
	if (amount == -1)
		return (NULL);
	else if (amount == -2)
	{
		while (cmd_data && !data_is_pipe(cmd_data))
			cmd_data = cmd_data->next;
		return (cmd_data);
	}
	return (cmd_data);
}

t_list	*made_massive_command(t_list *cmd_data, int amount, t_cmd *s)
{
	char	**command;
	int		i;

	i = 0;
	command = malloc(sizeof(char *) * (amount + 1));
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (cmd_data && data_redirect_and_heredoc(cmd_data))
			cmd_data = cmd_data->next->next;
		else
		{
			if ((cmd_data->flag_dollar_expanded && *(cmd_data->content))
				|| !(cmd_data->flag_dollar_expanded))
			{
				command[i] = ft_strdup(cmd_data->content);
				i++;
			}
			cmd_data = cmd_data->next;
		}
	}
	command[i] = NULL;
	s->cmd = command;
	return (cmd_data);
}

void	add_command_and_args(t_list *cmd_data, t_cmd *s)
{
	int	amount;

	while (cmd_data)
	{
		if (s->err)
			cmd_data = skip_error_process(cmd_data, s);
		else
		{
			amount = count_amount_of_args(cmd_data);
			if (amount == -1 || amount == -2)
				cmd_data = skip_pipe_data(cmd_data, amount, s);
			else
				cmd_data = made_massive_command(cmd_data, amount, s);
		}
		if (cmd_data && data_is_pipe(cmd_data))
		{
			s = s->next;
			cmd_data = cmd_data->next;
		}
	}
}
