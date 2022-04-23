#include "minishell.h"

void	change_data_in_list(t_env *env, char *data)
{
	free(env->data);
	env->data = ft_strdup(data);
}

void	env_build_in(t_env *env, t_cmd *s)
{
	while (env)
	{
		if (ft_strrchr(env->data, '='))
		{
			ft_putstr_fd(env->data, s->out);
			write(s->out, "\n", 1);
		}
		env = env->next;
	}
	g_return_code = 0;
}