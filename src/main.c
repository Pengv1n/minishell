#include "minishell.h"
#include "stdio.h"

int	main(int argc, char **argv, char **envm)
{
	t_env	*env;

	env = crt_env(envm);
	while (env->next)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
	return (0);
}