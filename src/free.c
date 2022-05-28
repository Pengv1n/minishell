/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:55:54 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:55:55 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		if (env->data)
			free(env->data);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

void	free_msh(t_msh *msh)
{
	if (msh)
	{
		if (msh->pwd)
		{
			free(msh->pwd);
			msh->pwd = NULL;
		}
		if (msh->old_pwd)
		{
			free(msh->old_pwd);
			msh->old_pwd = NULL;
		}
		free(msh);
		msh = NULL;
	}
}
