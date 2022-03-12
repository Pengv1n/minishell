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

	env = crt_env(envm);
	while (env->next)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
	free_env(env);
	return (0);
}