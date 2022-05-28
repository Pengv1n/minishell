/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:37:41 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 23:38:18 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_env(t_env *orig, t_env *new)
{
	t_env	*last;

	while (orig->next)
	{
		if (orig->next && !ft_strncmp(orig->next->data,
				new->data, ft_strlen(orig->next->data)))
		{
			last = orig->next;
			orig->next = orig->next->next;
			last->next = NULL;
		}
		else
			orig = orig->next;
	}
	if (last)
	{
		free(last->data);
		free(last);
	}
}

static t_env	*copy_env(t_env *env)
{
	t_env	*orig;

	orig = env->next;
	free(env->data);
	env->data = NULL;
	free(env);
	env = NULL;
	return (orig);
}

void	unset_build_in(t_cmd *s, t_env **env)
{
	t_env	*new;
	int		num;

	if (!(*env) || !(s->cmd[1]))
		return ;
	num = 0;
	g_return_code = 0;
	while (s->cmd[++num])
	{
		if (check_for_error_data(s->cmd[num], 'u'))
			;
		new = find_env_data(*env, s->cmd[num]);
		if (new)
		{
			if (!ft_strncmp((*env)->data, new->data,
					ft_strlen((*env)->data)))
				*env = copy_env(*env);
			else
				next_env(*env, new);
		}
	}
}
