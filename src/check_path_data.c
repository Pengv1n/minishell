/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:49:32 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 17:49:33 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_dollar_question(t_list *cmd_data, int i, char *data)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;
	int		len;

	tmp1 = ft_substr(data, 0, i - 1);
	ret = ft_itoa(g_return_code);
	len = ft_strlen(ret);
	tmp2 = ft_strjoin(tmp1, ret);
	free(tmp1);
	free(ret);
	tmp1 = ft_strdup(data + i + 1);
	free(cmd_data->content);
	cmd_data->content = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	return (i + len - 1);
}

int	data_dollar_num(t_list *cmd_data, int i, char *data)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(data, 0, i - 1);
	tmp2 = ft_strdup(data + i + 1);
	free(cmd_data->content);
	cmd_data->content = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (i);
}

char	*check_in_env(char *var, t_env *env)
{
	int		len;
	char	*new;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(var, env->data, len) && env->data[len] == '=')
		{
			new = ft_memchr(env->data, '=', ft_strlen(env->data));
			new++;
			return (ft_strdup(new));
		}
		env = env->next;
	}
	return (NULL);
}

int	data_change_path(t_list *data, int i, char *str, t_env *env)
{
	int		start;
	char	*new;
	char	*tmp;
	int		len;
	int		start_and_i[2];

	start = i;
	i = check_path(i, str);
	if (start == i)
		return (i);
	tmp = ft_substr(str, start, i - start);
	new = check_in_env(tmp, env);
	free(tmp);
	if (!new)
	{
		free(data->content);
		data->content = ft_strdup("");
		return (start - 1);
	}
	start_and_i[0] = start;
	start_and_i[1] = i;
	len = data_change_path_utils(str, start_and_i, new, data);
	return (start + len - 1);
}

int	check_path_data(t_list *cmd_data, int i, char *data, t_env *env)
{
	if (cmd_data->flag_not_change_dollars == 1)
		return (check_path(i, data));
	if (data[i] == '?')
	{
		i = data_dollar_question(cmd_data, i--, data);
		return (i);
	}
	if (data[i] && ft_isdigit(data[i]))
	{
		i = data_dollar_num(cmd_data, i--, data);
		return (i);
	}
	if (data[i] && (ft_isalnum((int)data[i]) || data[i] == '_'))
		i = data_change_path(cmd_data, i, data, env);
	return (i);
}
