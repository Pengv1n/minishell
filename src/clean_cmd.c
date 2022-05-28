/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:02:43 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 18:02:52 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_one_quote(t_list *cmd_data, int i, char *data)
{
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*new;

	j = i + 1;
	while (data[j] && data[j] != '\'')
		j++;
	if (!data[j])
		return (i + 1);
	tmp1 = ft_substr(data, 0, i);
	tmp2 = ft_substr(data, i + 1, j - i - 1);
	new = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_strdup(data + j + 1);
	tmp2 = ft_strjoin(new, tmp1);
	free(tmp1);
	free(new);
	free(cmd_data->content);
	cmd_data->content = tmp2;
	return (j + 1 - 2);
}

int	del_two_quote(t_list *cmd_data, int start, char *data, int finish)
{
	char	*tmp1;
	char	*tmp2;
	char	*new;

	tmp1 = ft_substr(data, 0, start);
	tmp2 = ft_substr(data, start + 1, finish - start - 1);
	new = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp2 = ft_strdup(data + finish + 1);
	tmp1 = ft_strjoin(new, tmp2);
	free(new);
	free(tmp2);
	free(cmd_data->content);
	cmd_data->content = tmp1;
	return (finish - 2);
}

int	delete_two_quote(t_list *cmd_data, int i, char *data, t_env *env)
{
	int	j;

	j = i + 1;
	while (data[j] && data[j] != '\"')
		j++;
	if (!data[j])
		return (i + 1);
	j = i + 1;
	while (data[j] && data[j] != '\"')
	{
		if (data[j] == '$')
		{
			j = check_path_data(cmd_data, ++j, data, env);
			data = cmd_data->content;
		}
		if (data[j] != '\"')
			j++;
	}
	j = del_two_quote(cmd_data, i, data, j);
	return (j + 1);
}

void	check_arg(t_list *cmd_data, t_env *env)
{
	char	*data;
	int		i;

	i = 0;
	data = cmd_data->content;
	while (data[i])
	{
		if (!(data[i] == '\'' || data[i] == '\"' || data[i] == '$'))
			i++;
		if (data[i] == '\'')
		{
			i = delete_one_quote(cmd_data, i, data);
			cmd_data->flag_in_quotes = 1;
			data = cmd_data->content;
		}
		if (data[i] == '$')
			data = do_change_path(cmd_data, data, &i, env);
		if (data[i] == '\"')
		{
			i = delete_two_quote(cmd_data, i, data, env);
			cmd_data->flag_in_quotes = 1;
			data = cmd_data->content;
		}
	}
}

void	clean_commands(t_list *cmd_data, t_env *env)
{
	while (cmd_data)
	{
		cmd_data->flag_in_quotes = 0;
		check_arg(cmd_data, env);
		cmd_data = cmd_data->next;
	}
}
