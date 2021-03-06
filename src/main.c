/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 00:07:46 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/23 00:07:47 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

t_env	*find_env(t_env *env, char *data)
{
	int	len;

	len = 0;
	if (ft_strchr(data, '='))
		len = ft_strchr_len(data, '=');
	else
		len = ft_strlen(data);
	while (env)
	{
		if (!ft_strncmp(data, env->data, len)
			&& (env->data[len] == '=' || !env->data[len]))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	edit_env(t_env **env)
{
	t_env	*f_env;
	int		n;
	char	*str_n;

	f_env = find_env(*env, "SHLVL=");
	if (!f_env)
		add_back_env(env, new_env("SHLVL=1"));
	else
	{
		n = ft_atoi(f_env->data + 6);
		n++;
		str_n = ft_itoa(n);
		free(f_env->data);
		f_env->data = ft_strjoin("SHLVL=", str_n);
		free(str_n);
	}
}

void	pwd(t_msh *msh, t_env *env)
{
	t_env	*f_pwd;

	msh->pwd = NULL;
	msh->old_pwd = NULL;
	f_pwd = find_env(env, "PWD=");
	if (f_pwd)
		msh->pwd = ft_strdup(f_pwd->data + 4);
	f_pwd = find_env(env, "OLDPWD=");
	if (f_pwd)
		msh->old_pwd = ft_strdup(f_pwd->data + 7);
}

void	handler_command(t_msh *msh, t_env **env)
{
	char	*command;

	command = readline("minishell$ ");
	if (!command)
	{
		ft_putendl_fd("exit", 1);
		exit_minishell();
	}
	if (ft_strlen(command) > 0)
		add_history(command);
	if (*command)
		parse_command(command, msh, env);
	free(command);
}

int	main(int argc, char **argv, char **envm)
{
	t_env	*env;
	t_msh	*msh;

	(void)argc;
	(void)argv;
	msh = (t_msh *) malloc(sizeof(t_msh));
	if (!msh)
		error_with_std_function(1);
	env = crt_env(envm);
	edit_env(&env);
	pwd(msh, env);
	while (1)
	{
		sig_msh();
		handler_command(msh, &env);
	}
	rl_clear_history();
	free_env(env);
	free_msh(msh);
	return (0);
}
