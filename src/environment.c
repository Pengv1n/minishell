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
