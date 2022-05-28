/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:43:22 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:43:22 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_redirect_in(t_list *cmd_data)
{
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(cmd_data->content, "<", 2))
		return (1);
	return (0);
}

int	data_redirect_out(t_list *cmd_data)
{
	if (cmd_data->flag_in_quotes)
		return (0);
	if (!ft_strncmp(cmd_data->content, ">", 2)
		|| !ft_strncmp(cmd_data->content, ">>", 3))
		return (1);
	return (0);
}

int	check_if_not_last_redirect_in(t_list *cmd_data)
{
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (data_redirect_in(cmd_data))
			return (1);
		cmd_data = cmd_data->next;
	}
	return (0);
}

int	check_if_not_last_redirect_out(t_list *cmd_data)
{
	while (cmd_data && !data_is_pipe(cmd_data))
	{
		if (data_redirect_out(cmd_data))
			return (1);
		cmd_data = cmd_data->next;
	}
	return (0);
}

int	data_change_path_utils(char *str, int *start_and_i, char *new, t_list *data)
{
	char	*tmp;
	int		len;
	char	*tmp2;

	tmp = ft_substr(str, 0, start_and_i[0] - 1);
	len = ft_strlen(new);
	tmp2 = ft_strjoin(tmp, new);
	free(new);
	free(tmp);
	tmp = ft_strdup(str + start_and_i[1]);
	free(data->content);
	data->content = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (len);
}
