/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:59:56 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/22 18:00:17 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_build_in_function(t_env **env, t_cmd *s, t_msh *msh, int flag)
{
	char	*cmd;

	cmd = s->cmd[0];
	if (!ft_strncmp(cmd, "echo", 5))
		echo_build_in(s);
	else if (!ft_strncmp(cmd, "pwd", 4))
		pwd_build_in(s, msh);
	else if (!ft_strncmp(cmd, "env", 4))
		env_build_in(*env, s);
	else if (!ft_strncmp(cmd, "export", 7))
		export_build_in(env, s);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_build_in(s);
	else if (!ft_strncmp(cmd, "unset", 6))
		unset_build_in(s, env);
	else if (!ft_strncmp(cmd, "cd", 3))
	{
		cd_build_in(s->cmd, *env, msh->pwd);
		change_env_pwds(msh, *env);
	}
	close_inout(s);
	if (flag == 1)
		exit(EXIT_SUCCESS);
}

int	check_if_build_in_or_null(t_env **env, t_cmd *s, t_msh *msh, int flag)
{
	char	*cmd;

	if (!s->cmd)
	{
		close_inout(s);
		return (1);
	}
	cmd = s->cmd[0];
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "exit", 5))
	{
		if (flag == 1)
			choose_build_in_function(env, s, msh, 0);
		return (1);
	}
	return (0);
}
