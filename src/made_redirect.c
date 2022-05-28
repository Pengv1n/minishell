/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:42:25 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:42:45 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_redirect(t_list *cmd_data)
{
	char	*tmp;

	tmp = cmd_data->content;
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(tmp, ">", 2) || !ft_strncmp(tmp, "<", 2)
		|| !ft_strncmp(tmp, ">>", 3))
		return (1);
	return (0);
}

t_list	*open_in_files(t_list *cmd_data, t_cmd *s)
{
	s->in = open(cmd_data->next->content, O_RDONLY, 0644);
	if (s->in < 0)
	{
		cmd_data = error_with_redirect(cmd_data, s);
		return (cmd_data);
	}
	if (check_if_not_last_redirect_in(cmd_data->next))
		close(s->in);
	return (cmd_data->next->next);
}

t_list	*open_out_files(t_list *cmd_data, t_cmd *s)
{
	if (!ft_strncmp(cmd_data->content, ">", 2))
		s->out = open(cmd_data->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(cmd_data->content, ">>", 3))
		s->out = open(cmd_data->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (s->out < 0)
	{
		cmd_data = error_with_redirect(cmd_data, s);
		return (cmd_data);
	}
	if (check_if_not_last_redirect_out(cmd_data->next))
		close(s->out);
	return (cmd_data->next->next);
}

t_list	*open_redirect(t_list *cmd_data, t_cmd *s)
{
	if (cmd_data->flag_ambitious_redirect)
	{
		cmd_data = error_ambitious_data(cmd_data, s);
		return (cmd_data);
	}
	if (data_redirect_in(cmd_data))
		cmd_data = open_in_files(cmd_data, s);
	else if (data_redirect_out(cmd_data))
		cmd_data = open_out_files(cmd_data, s);
	return (cmd_data);
}

void	made_redirect(t_list *cmd_data, t_cmd *s)
{
	while (cmd_data)
	{
		if (data_redirect(cmd_data))
			cmd_data = open_redirect(cmd_data, s);
		else
			cmd_data = cmd_data->next;
		if (cmd_data && data_is_pipe(cmd_data))
		{
			s = s->next;
			cmd_data = cmd_data->next;
		}
	}
}
