/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_path_not_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:46:29 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 17:46:30 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(int i, char *str)
{
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void	check_cmd(t_list **cmd_data, t_env *env)
{
	char	*next_op;

	next_op = (*cmd_data)->next->content;
	next_op = check_in_env(next_op + 1, env);
	if (!next_op)
	{
		(*cmd_data)->amb_data = ft_strdup((*cmd_data)->next->content);
		(*cmd_data)->flag_ambitious_redirect = 1;
	}
	else
		free(next_op);
}

void	check_if_change(t_list **cmd_data, t_env *env)
{
	char	*op;
	char	*next_op;

	op = (*cmd_data)->content;
	if ((*cmd_data)->next)
	{
		next_op = (*cmd_data)->next->content;
		if ((!ft_strncmp(op, ">", 2) || !ft_strncmp(op, "<", 2)
				|| !ft_strncmp(op, ">>", 3)) && next_op[0] == '$')
		{
			if (ft_strlen(next_op) > 1 && check_path(0, next_op + 1) > 0)
				check_cmd(cmd_data, env);
		}
	}
	if (!ft_strncmp(op, "<<", 3))
	{
		if (!(*cmd_data)->next)
			return ;
		(*cmd_data)->next->flag_not_change_dollars = 1;
	}
}

void	check_if_path_not_expand(t_list *cmd_data, t_env *env)
{
	while (cmd_data)
	{
		check_if_change(&cmd_data, env);
		cmd_data = cmd_data->next;
	}
}
