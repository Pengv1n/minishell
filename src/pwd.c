/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:28:32 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:28:33 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_build_in(t_cmd *s, t_msh *msh)
{
	char	*buf;

	buf = get_address();
	if (!buf)
		ft_putendl_fd(msh->pwd + 4, s->out);
	else
	{
		ft_putendl_fd(buf, s->out);
		free(buf);
	}
	g_return_code = 0;
}
