/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_cmd_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:28:20 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:28:21 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_cmd_struct(t_list *cmd_data, t_cmd *s)
{
	heredoc(cmd_data, s);
	made_redirect(cmd_data, s);
	add_command_and_args(cmd_data, s);
}
