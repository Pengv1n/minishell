#include "minishell.h"

t_env	*new_env(char *data)
{
	t_env	*e;

	e = (t_env *) malloc(sizeof(t_env));
	if (!e)
		exit(EXIT_FAILURE);
	e->data = data;
	e->next = NULL;
	return (e);
}

t_env	*lst_end(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
		*env = new;
	else
	{
		tmp = lst_end(*env);
		tmp->next = new;
		new->next = NULL;
	}
}

t_env	*crt_env(char **env)
{
	t_env	*e;
	char	*data;

	e = NULL;
	while (*env)
	{
		data = ft_strdup(*env);
		add_back_env(&e, new_env(data));
		env++;
	}
	return (e);
}

int	size_env(t_env *env)
{
	int	ret;

	ret = 0;
	while (env)
	{
		env = env->next;
		ret++;
	}
	return (ret);
}

t_env	*find_env_data(t_env *env, char *data)
{
	int len;

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