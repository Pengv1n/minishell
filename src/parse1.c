/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:02:30 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:02:31 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_data(t_list *cmd_data)
{
	int	i;

	i = 0;
	while (cmd_data)
	{
		cmd_data->flag_not_change_dollars = 0;
		cmd_data->flag_ambitious_redirect = 0;
		cmd_data->flag_dollar_expanded = 0;
		cmd_data->flag_in_quotes = 0;
		cmd_data->amb_data = NULL;
		cmd_data->num = i;
		cmd_data = cmd_data->next;
		i++;
	}
}

void	parse_command(char *command, t_msh *msh, t_env **env)
{
	t_list	*cmd_data;
	t_cmd	*s;

	cmd_data = NULL;
	s = NULL;
	split_cmd(command, &cmd_data);
	if (!cmd_data)
		return ;
	init_cmd_data(cmd_data);
	check_if_path_not_expand(cmd_data, *env);
	clean_commands(cmd_data, *env);
	if (check_syntax_error(cmd_data)
		|| check_repited_redirect(cmd_data))
	{
		g_return_code = 258;
		ft_lstclear(&cmd_data, (void *)free);
		return ;
	}
	if (!init_cmd_struct(cmd_data, &s, msh))
		return ;
	fill_list_cmd_struct(cmd_data, s);
	pipex(s, msh, *env);
	ft_lstclear(&cmd_data, (void *)free);
	clear_list_cmd_struct(&s);
}
