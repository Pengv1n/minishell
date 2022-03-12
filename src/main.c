#include "minishell.h"
#include "stdio.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->data);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

t_env	*find_env(t_env *env, char *data)
{
	int	len;

	len = 0;
	if (ft_strchr(data, '='))
		while (data[len] && data[len] != '=')
			len++;
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
	int	n;
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
	f_env = find_env(*env, "OLDPWD=");
	if (f_env)
	{
		free(f_env->data);
		f_env->data = ft_strdup("OLDPWD");
	}
}

void	pwd()

int	main(int argc, char **argv, char **envm)
{
	t_env	*env;
	t_env	*tmp;

	env = crt_env(envm);
	edit_env(&env);
	tmp = env;
	while (tmp->next)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	free_env(env);
	return (0);
}