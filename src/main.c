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

int	main(int argc, char **argv, char **envm)
{
	t_env	*env;
	t_env	*tmp;

	env = crt_env(envm);
	tmp = env;
	while (tmp->next)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	free_env(env);
	return (0);
}