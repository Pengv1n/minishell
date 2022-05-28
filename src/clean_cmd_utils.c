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

char	*do_change_path(t_list *cmd_data, char *data, int *i, t_env *env)
{
	*i = check_path_data(cmd_data, (++(*i)), data, env);
	cmd_data->flag_dollar_expanded = 1;
	data = cmd_data->content;
	return (data);
}
