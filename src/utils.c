/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:29:58 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:30:00 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_str_num(char *data)
{
	while (*data == ' ')
		data++;
	if (*data == '+' || *data == '-')
		data++;
	while (*data)
	{
		if (!ft_isdigit(*data))
			return (0);
		data++;
	}
	return (1);
}

int	data_redirect_and_heredoc(t_list *cmd_data)
{
	char	*tmp;

	tmp = cmd_data->content;
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(tmp, ">", 2) || !ft_strncmp(tmp, "<", 2)
		|| !ft_strncmp(tmp, ">>", 3) || !ft_strncmp(tmp, "<<", 3))
		return (1);
	return (0);
}

void	free_double_massive(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		free(data[i]);
		data[i] = NULL;
	}
	free(data);
	data = NULL;
}

void	clear_list_cmd_struct(t_cmd **s)
{
	t_cmd	*tmp;

	if (!(*s))
		return ;
	while (*s)
	{
		if ((*s)->hr_name)
		{
			unlink((*s)->hr_name);
			free((*s)->hr_name);
			(*s)->hr_name = NULL;
		}
		if ((*s)->cmd)
		{
			free_double_massive((*s)->cmd);
		}
		tmp = (*s)->next;
		free(*s);
		*s = tmp;
	}
	*s = NULL;
}

int	ft_strchr_len(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}
